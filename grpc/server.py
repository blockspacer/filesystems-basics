import contextlib
import logging
import multiprocessing
import random
import socket
import string
import sys
import time
from concurrent import futures

import grpc

import generator_pb2
import generator_pb2_grpc


class Generator(generator_pb2_grpc.GeneratorServicer):
    def __init__(self):
        self.counter = random.randint(0, 99)
        self.char_set = string.ascii_letters + string.digits

    def generate(self, request, context):
        self.counter += 1
        if self.counter % 100 == 0:
            time.sleep(1)
        random_string = ''.join(random.choices(self.char_set, k=8))  # 128
        return generator_pb2.GenReply(text=random_string)


def _run_server(bind_address):
    logging.info('Starting new server.')

    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=multiprocessing.cpu_count()),
        options=(('grpc.so_reuseport', 1),))
    generator_pb2_grpc.add_GeneratorServicer_to_server(Generator(), server)
    server.add_insecure_port(bind_address)
    server.start()
    server.wait_for_termination()


@contextlib.contextmanager
def _reserve_port():
    """Find and reserve a port for all subprocesses to use."""
    sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    if sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT) == 0:
        raise RuntimeError('Failed to set SO_REUSEPORT.')
    sock.bind(('', 0))
    try:
        yield sock.getsockname()[1]
    finally:
        sock.close()


def main():
    with _reserve_port() as port:
        logging.info(f'Binding to localhost:{port}')
        sys.stdout.flush()

        workers = []
        for _ in range(multiprocessing.cpu_count()):
            worker = multiprocessing.Process(
                target=_run_server, args=(f'localhost:{port}',)
            )
            worker.start()
            workers.append(worker)
        map(lambda w: w.join(), workers)


if __name__ == '__main__':
    logging.basicConfig(
        format='%(asctime)s.%(msecs)03d %(message)s',
        datefmt='%H:%M:%S',
        level=logging.INFO,
    )
    main()

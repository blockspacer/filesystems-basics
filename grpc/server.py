import logging
import multiprocessing
import random
import string
import sys
import time
from concurrent import futures

import grpc

import generator_pb2
import generator_pb2_grpc
from utils import _reserve_port, write_config


class Generator(generator_pb2_grpc.GeneratorServicer):
    def __init__(self):
        self.counter = random.randint(0, 99)
        self.char_set = string.ascii_letters + string.digits

    def generate(self, request, context):
        self.counter += 1
        if self.counter % 100 == 0:
            time.sleep(1)
        random_string = ''.join(random.choices(self.char_set, k=128))
        return generator_pb2.GenReply(text=random_string)


def _run_server(bind_address):
    logging.info(f'Starting new server on {bind_address}')

    server = grpc.server(
        futures.ThreadPoolExecutor(max_workers=multiprocessing.cpu_count()),
        options=(('grpc.so_reuseport', 1),))
    generator_pb2_grpc.add_GeneratorServicer_to_server(Generator(), server)
    server.add_insecure_port(bind_address)
    server.start()
    server.wait_for_termination()


def main():
    logging.basicConfig(
        format='%(asctime)s.%(msecs)03d %(message)s',
        datefmt='%H:%M:%S',
        level=logging.INFO,
    )
    with _reserve_port() as port:
        server_address = f'localhost:{port}'
        write_config('server_address', server_address)
        sys.stdout.flush()

        # _run_server(server_address) # single processed execution
        workers = []
        for _ in range(multiprocessing.cpu_count()):
            worker = multiprocessing.Process(
                target=_run_server, args=(server_address,)
            )
            worker.start()
            workers.append(worker)
        map(lambda w: w.join(), workers)


if __name__ == '__main__':
    main()

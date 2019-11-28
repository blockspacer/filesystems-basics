import logging
import multiprocessing
from concurrent import futures

import grpc

import generator_pb2
import generator_pb2_grpc
from utils import _reserve_port, read_config, write_config

PROCESS_NUMBER = 4  # 16

_worker_channel_singleton = None
_worker_stub_singleton = None


class Proxy(generator_pb2_grpc.ProxyServicer):
    def __init__(self, server_address):
        self.server_address = server_address

    def generate(self, request, context):
        with grpc.insecure_channel(self.server_address) as channel:
            stub = generator_pb2_grpc.GeneratorStub(channel)
            response = stub.generate(generator_pb2.GenRequest())
            return response


def _run_proxy(server_address, bind_address):
    logging.info(f'Starting new proxy on {bind_address}')
    proxy = grpc.server(futures.ThreadPoolExecutor(
        max_workers=multiprocessing.cpu_count()))
    generator_pb2_grpc.add_ProxyServicer_to_server(
        Proxy(server_address), proxy)
    proxy.add_insecure_port(bind_address)
    proxy.start()
    proxy.wait_for_termination()


def main():
    logging.basicConfig(
        format='%(asctime)s.%(msecs)03d %(message)s',
        datefmt='%H:%M:%S',
        level=logging.INFO,
    )
    with _reserve_port() as port:
        server_address = read_config('server_address')
        proxy_address = f'localhost:{port}'
        write_config('proxy_address', proxy_address)
        _run_proxy(server_address, proxy_address)


if __name__ == '__main__':
    main()

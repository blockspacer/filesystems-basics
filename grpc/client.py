import argparse
import atexit
import logging
import multiprocessing

import grpc

import generator_pb2
import generator_pb2_grpc

PROCESS_NUMBER = 4  # 16

_worker_channel_singleton = None
_worker_stub_singleton = None


def _shutdown_worker():
    logging.info('Shutting worker process down.')
    if _worker_channel_singleton is not None:
        _worker_channel_singleton.stop()


def _initialize_worker(server_address):
    logging.info('Initializing worker process.')
    global _worker_channel_singleton
    global _worker_stub_singleton
    _worker_channel_singleton = grpc.insecure_channel(server_address)
    _worker_stub_singleton = generator_pb2_grpc.GeneratorStub(
        _worker_channel_singleton)
    atexit.register(_shutdown_worker)


def _run_worker_query(_):
    return _worker_stub_singleton.generate(generator_pb2.GenRequest())


def generate_string(server_address: str, process_number: int):
    worker_pool = multiprocessing.Pool(
        processes=process_number,
        initializer=_initialize_worker,
        initargs=(server_address,),
    )
    result = worker_pool.map(_run_worker_query, range(process_number))
    return ''.join([i.text for i in result])


def main():
    logging.basicConfig(
        format='%(asctime)s.%(msecs)03d %(message)s',
        datefmt='%H:%M:%S',
        level=logging.INFO,
    )
    parser = argparse.ArgumentParser()
    parser.add_argument('server_address')
    args = parser.parse_args()
    print(generate_string(args.server_address, PROCESS_NUMBER))


if __name__ == '__main__':
    main()

import argparse
import atexit
import logging
import multiprocessing
import operator
import sys

import grpc

import generator_pb2
import generator_pb2_grpc

_PROCESS_COUNT = 4  # 16
_MAXIMUM_CANDIDATE = 100

_worker_channel_singleton = None
_worker_stub_singleton = None

logger = logging.getLogger(__name__)


def _shutdown_worker():
    logger.info('Shutting worker process down.')
    if _worker_channel_singleton is not None:
        _worker_channel_singleton.stop()


def _initialize_worker(server_address):
    global _worker_channel_singleton  # pylint: disable=global-statement
    global _worker_stub_singleton  # pylint: disable=global-statement
    logger.info('Initializing worker process.')
    _worker_channel_singleton = grpc.insecure_channel(server_address)
    _worker_stub_singleton = generator_pb2_grpc.GeneratorStub(
        _worker_channel_singleton)
    atexit.register(_shutdown_worker)


def _run_worker_query(tmp):
    return _worker_stub_singleton.generate(generator_pb2.GenRequest())


def _calculate_primes(server_address):
    worker_pool = multiprocessing.Pool(
        processes=_PROCESS_COUNT,
        initializer=_initialize_worker,
        initargs=(server_address,),
    )
    primality = worker_pool.map(_run_worker_query, range(100))
    primes = zip(range(100), map(operator.attrgetter('text'), primality))
    return tuple(primes)


def main():
    msg = f'Determine the primality of the first {_MAXIMUM_CANDIDATE} integers.'
    parser = argparse.ArgumentParser(description=msg)
    parser.add_argument(
        'server_address',
        help='The address of the server (e.g. localhost:50051)')
    args = parser.parse_args()
    primes = _calculate_primes(args.server_address)
    print(primes)


if __name__ == '__main__':
    handler = logging.StreamHandler(sys.stdout)
    formatter = logging.Formatter('[PID %(process)d] %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    logger.setLevel(logging.INFO)
    main()

import argparse
from datetime import datetime

import grpc
from termcolor import colored

import generator_pb2
import generator_pb2_grpc


def run(server_address: str, request_number: int):
    with grpc.insecure_channel(server_address) as channel:
        stub = generator_pb2_grpc.GeneratorStub(channel)
        for i in range(request_number):
            start = datetime.now()
            response = stub.generate(generator_pb2.GenRequest())
            timedelta = round((datetime.now() - start).total_seconds() * 1000, 1)
            color = 'red' if timedelta >= 1000 else 'green'
            print(colored(f'[{i}] {response.text} Time: {timedelta} ms', color))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('server_address')
    args = parser.parse_args()
    run(args.server_address, 100)


if __name__ == '__main__':
    main()

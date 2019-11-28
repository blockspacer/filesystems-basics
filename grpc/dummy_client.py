import argparse
from datetime import datetime

import grpc
from termcolor import colored

import generator_pb2
import generator_pb2_grpc
from utils import compress_string


def run(server_address: str, request_number: int) -> str:
    result = ''
    with grpc.insecure_channel(server_address) as channel:
        # stub = generator_pb2_grpc.GeneratorStub(channel)
        stub = generator_pb2_grpc.ProxyStub(channel)
        for i in range(request_number):
            start = datetime.now()
            response = stub.generate(generator_pb2.GenRequest())
            timedelta = round((datetime.now() - start).total_seconds() * 1000, 1)
            color = 'red' if timedelta >= 1000 else 'green'
            print(colored(f'[{i}] {compress_string(response.text)} '
                          f'Time: {timedelta} ms', color))
            result += response.text
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('server_address')
    args = parser.parse_args()
    generated_string = run(args.server_address, 100)
    print(f'Length: {len(generated_string)}')
    print(compress_string(generated_string))


if __name__ == '__main__':
    main()

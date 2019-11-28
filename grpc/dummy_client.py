from datetime import datetime

import grpc
from termcolor import colored

import generator_pb2
import generator_pb2_grpc
from utils import compress_string, read_config


def run(server_address: str, request_number: int, use_proxy: bool) -> str:
    result = ''
    with grpc.insecure_channel(server_address) as channel:
        stub = generator_pb2_grpc.ProxyStub(channel) if use_proxy \
            else generator_pb2_grpc.GeneratorStub(channel)
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
    use_proxy = read_config('use_proxy')
    server_address = read_config('proxy_address') if use_proxy else read_config('server_address')
    generated_string = run(server_address, 100, read_config('use_proxy'))
    print(f'Length: {len(generated_string)}')
    print(compress_string(generated_string))


if __name__ == '__main__':
    main()

import contextlib
import logging
import socket
from configparser import ConfigParser

from termcolor import colored

logging.basicConfig(
    format='%(asctime)s.%(msecs)03d: %(message)s',
    datefmt='%H:%M:%S',
    level=logging.INFO,
)


def compress_string(string: str, limit: int = 20) -> str:
    return string[:limit] + ' ... ' + string[-limit:]


@contextlib.contextmanager
def _reserve_port():
    sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    if sock.getsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT) == 0:
        raise RuntimeError('Failed to set SO_REUSEPORT.')
    sock.bind(('', 0))
    try:
        yield sock.getsockname()[1]
    finally:
        sock.close()


def write_config(key: str, value: str):
    config = ConfigParser()
    config.read('config.ini')
    config['ADDRESSES'][key] = value
    with open('config.ini', 'w') as configfile:
        config.write(configfile)


def read_config(key: str) -> str:
    config = ConfigParser()
    config.read('config.ini')
    section = config['ADDRESSES']
    return section.getboolean(key) if key == 'use_proxy' else section[key]


def green_print(string):
    print(colored(string, 'green'))

def compress_string(string: str, limit: int = 20) -> str:
    return string[:limit] + ' ... ' + string[-limit:]

import subprocess
import base64
import random
import os

def random_bytes(size, bad_bytes=None):
    if bad_bytes is None:
        bad_bytes = []
    data = bytearray()
    while len(data) < size:
        b = random.randint(0, 255)
        if b not in bad_bytes:
            data.append(b)
    return bytes(data)

def test_encode():
    for size in [10, 100, 1000]:
        data = random_bytes(size, bad_bytes=[10])
        expected = base64.a85encode(data)
        proc = subprocess.run(["./encoder"], input=data, stdout=subprocess.PIPE)
        actual = proc.stdout.strip()
        if actual != expected:
            print(f"encode failed at size {size}")
            return
        print(f"test of {size} bytes is successful")

    print("encode OK")

def test_decode():
    for size in [10, 100, 1000]:
        data = bytes([random.randint(33, 117) for _ in range(size)])
        encoded = base64.a85encode(data)
        decoded = base64.a85decode(encoded)
        proc = subprocess.run(["./decoder"], input=encoded, stdout=subprocess.PIPE)
        actual = proc.stdout.strip()
        if actual != decoded:
            print(f"decode failed at size {size}")
            return
        print(f"test of {size} bytes is successful")
    print("decode OK")

def test_decode_err():
    for size in range(10, 20):
        data = bytes([random.randint(33, 117) for _ in range(size)])
        a= random.randint(1, 33)
        data += bytes(a)
        encoded = base64.a85encode(data)
        decoded = base64.a85decode(encoded)
        proc = subprocess.run(["./decoder"], input=encoded, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        actual = proc.stdout.strip()
        if proc.returncode != 1:
            print(f"decode error is not catched at size {size}")
            return
        print(f"test of error in {size} bytes is successfully cathed")
    for size in range(10, 20):
        data = bytes([random.randint(33, 117) for _ in range(size)])
        a= random.randint(117, 256)
        data += bytes(a)
        encoded = base64.a85encode(data)
        decoded = base64.a85decode(encoded)
        proc = subprocess.run(["./decoder"], input=encoded, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        actual = proc.stdout.strip()
        if proc.returncode != 1:
            print(f"decode error is not catched at size {size}")
            return
        print(f"test of error in {size} bytes is successfully cathed")
    print("decode error is OK")

if __name__ == "__main__":
    if not os.path.exists("./encoder"):
        subprocess.run(["g++", "-o", "encoder", "encode.cpp", "coder.cpp", "coder.h"], check=True)
    if not os.path.exists("./decoder"):
        subprocess.run(["g++", "-o", "decoder", "decode.cpp", "coder.cpp", "coder.h"], check=True)

    test_encode()
    test_decode()
    test_decode_err()

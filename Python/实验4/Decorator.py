import time
def timed(fn):
    def run_time():
        start_time=time.perf_counter()
        fn()
        end_time=time.perf_counter()
        print('Run_time:',(end_time-start_time))
    return run_time

@timed
def test_plus():
    result = []
    for i in range(100000):
        result = result + [i]

@timed
def test_append():
    result = []
    for i in range(100000):
        result.append(i)

test_plus()
test_append()
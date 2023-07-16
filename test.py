from my_python_lib import new_thread, join_thread

def test():
    for i in range(10000):
        print("Hello World!")

new_thread(test)
test()
join_thread()
import time
time.sleep(1)

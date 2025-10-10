import subprocess
import time
import string
import os
import matplotlib.pyplot as plt
def a_string(length: int)->str:
    return "a" * length
kFieldString = a_string(int(1e6))
kSampleString = a_string(int(1e3))
kProgrammPath = "./lab2_var18/task" 
def benchmark_lab(max_thread: int, programm_path: str)->list[int]:
    result = [0 for _ in range(max_thread)]
    for i in range(max_thread):
        start_time = time.time()
        subprocess.run([programm_path, str(i+1)], input='\n'.join([kFieldString, kSampleString]), text=True, stdout=subprocess.PIPE)
        result[i] = time.time() - start_time
    return result
threadsCount = os.cpu_count()
results = benchmark_lab(threadsCount, kProgrammPath)
res_file = open("result.txt", "w")
res_file.write(' '.join(map(str, results)))
res_file.close()

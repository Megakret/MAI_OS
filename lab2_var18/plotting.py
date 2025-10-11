import matplotlib.pyplot as plt
with open("result.txt", "r") as res_file:
    results = list(map(float, res_file.readline().split()))
threadsCount = len(results)
T1 = results[0]
# Time plot
plt.plot(list(range(1,threadsCount+1)), results, 'o-')
plt.xlabel('Number of Threads')
plt.ylabel('Execution Time (s)')
plt.title('Execution time plot')
plt.grid(True)
plt.savefig("TimePlot.png", dpi=300) 
plt.close()

#Acceleration plot
acceleration_values = list(T1/res for res in results)
x_points = list(range(1, threadsCount+1))

plt.plot(x_points, acceleration_values, 'o-')
plt.plot([1, threadsCount], [1, threadsCount], 'r--', alpha=0.7)

for i, (x, y) in enumerate(zip(x_points, acceleration_values)):
    plt.annotate(f'{y:.2f}', (x, y), textcoords="offset points",
                 xytext=(0,10), ha='center', fontsize=9)

plt.xlabel('Number of Threads')
plt.ylabel('Acceleration')
plt.title("Acceleration Plot")
plt.grid(True)
plt.savefig("AccelerationPlot.png")
plt.close()

#Effectivness plot
plt.plot(list(range(1,threadsCount+1)), list(T1/res/(i+1) for i, res in enumerate(results)), 'o-')
plt.xlabel('Number of Threads')
plt.ylabel('Effectivness')
plt.title("Effectivness Plot")
plt.grid(True)
plt.savefig("EffectivnessPlot.png", dpi=300) 

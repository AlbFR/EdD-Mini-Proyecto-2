import sys
import matplotlib.pyplot as plt
import numpy as np

def readData(r, f, forward):
   ans = np.array([])
   for i in r:
      # enq_val, deq_val = f.readline().split(" ")
      val = f.readline()
      if val == "":
         raise ("Not enough data")
      val = float(val)
      # print(val)
      if forward:
         ans = np.append(ans, val)
      else:
         ans = np.append(val, ans)
   return ans

if len(sys.argv) < 1:
   raise ("At least one argument is needed, the amount of data")
n = int(sys.argv[1])

interval = 150
start = interval // 2

x = np.array([])
insertNode = np.array([])
deleteNode = np.array([])
at = np.array([])

f = open("data.txt", "r")

# Reads Vector enqueue data
r = range(start, n, interval)
insertNode = readData(r, f, True)
at = readData(r, f, True)
deleteNode = readData(r, f, False)

f.close()

x = np.linspace(start, n-start, n//interval + 1, endpoint=True)

# print(x)
print(insertNode)
print(at)
print(deleteNode)
# print(len(x))
# print(len(insertNode))
# print(len(deleteNode))
# print(len(at))

plt.plot(x, insertNode, color="red", label="insert")
plt.plot(x, at, color="green", label="at")
plt.plot(x, deleteNode, color="blue", label="delete")
plt.title("insertNode, at, deleteNode times compared to amount of data")
plt.xlabel("Input size")
plt.ylabel("Time in nanoseconds")
plt.legend()
plt.show()


# plt.plot(x, at, color="red", label="Vector")
# plt.plot(x, dequeue_heap, color="blue", label="Heap")
# plt.title("Dequeue time v/s data")
# plt.xlabel("Input size")
# plt.ylabel("Time in microseconds")
# plt.legend()
# plt.show()

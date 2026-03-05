from firebase import firebase
import matplotlib.pyplot as plt
import numpy as np
import secret
# put firebase link in secret.py

firebase = firebase.FirebaseApplication(secret.api_key, None)
result = firebase.get('/SlotsTest', None)
x = result.values()
money_array = []
win_array = []

for x, obj in result.items():
    money_array.append(obj['money'])
    win_array.append(obj['winAmt'])


plt.plot(money_array)
plt.xlabel("Attempts")
plt.ylabel("Money total")
plt.show()
plt.plot(win_array)
plt.xlabel("Attempts")
plt.ylabel("Money won")
plt.show()
print(money_array)
print(win_array)

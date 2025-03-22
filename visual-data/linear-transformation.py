import numpy as np
import matplotlib.pyplot as plt

# Defining a 2x3 matrix (transformation from R2 to R3)
A = np.array([[1, 2], [0, 1], [1, 0]])

# Singular Value Decomposition
U, S, VT = np.linalg.svd(A)

fig = plt.figure(figsize=(16, 4))

# Plotting the original vectors
ax1 = fig.add_subplot(141)
ax1.quiver(0, 0, 1, 0, color='r', angles = 'xy', scale_units = 'xy', scale=1)
ax1.quiver(0, 0, 0, 1, color='b', angles = 'xy', scale_units = 'xy', scale=1)
ax1.set_xlim([-3, 3])
ax1.set_ylim([-3, 3])
ax1.set_title('Original Vectors in R2')
ax1.set_xlabel('X')
ax1.set_ylabel('Y')

# Plotting the rotated vectors
ax2 = fig.add_subplot(142)
ax2.quiver(0, 0, VT[0, 0], VT[1, 0], color='r', angles = 'xy', scale_units = 'xy', scale=1)
ax2.quiver(0, 0, VT[0, 1], VT[1, 1], color='b', angles = 'xy', scale_units = 'xy', scale=1)
ax2.set_xlim([-3, 3])
ax2.set_ylim([-3, 3])
ax2.set_title('Rotated Vectors by V^T in R2')
ax2.set_xlabel('X')
ax2.set_ylabel('Y')

# Plotting the scaled vectors
X = np.matmul(np.diag(S), VT)
ax3 = fig.add_subplot(143)
ax3.quiver(0, 0, X[0, 0], X[1, 0], color='r', angles = 'xy', scale_units = 'xy', scale=1)
ax3.quiver(0, 0, X[0, 1], X[1, 1], color='b', angles = 'xy', scale_units = 'xy', scale=1)
ax3.set_xlim([-3, 3])
ax3.set_ylim([-3, 3])
ax3.set_title('Scaled Vectors by S in R2')
ax3.text(0.1, 0.5, f'σ = {round(S[0], 3)}, {round(S[1], 3)}', fontsize=12)
ax3.set_xlabel('X')
ax3.set_ylabel('Y')

# Plotting the rotated vectors in R3
ax3 = fig.add_subplot(144, projection='3d')
ax3.view_init(elev=20, azim=-80, roll=0)
ax3.quiver(0, 0, 0, X[0, 0], X[1, 0], 0, color='black')
ax3.quiver(0, 0, 0, X[0, 1], X[1, 1], 0, color='black')
ax3.quiver(0, 0, 0, A[0, 0], A[1, 0], A[2, 0], color='r')
ax3.quiver(0, 0, 0, A[0, 1], A[1, 1], A[2, 1], color='b')
ax3.set_xlim([-3,3])
ax3.set_ylim([-3,3])
ax3.set_zlim([-3,3])
ax3.set_title('Rotated Vectors by U in R3')
ax3.set_xlabel('X')
ax3.set_ylabel('Y')
ax3.set_zlabel('Z')

plt.tight_layout()
plt.show()
import csv
import matplotlib.pyplot as plt

# Read simulation results
with open("neutron_results.csv", "r") as file:
    data = list(csv.DictReader(file))

initial = [float(row["Initial_Energy"]) for row in data]
final = [float(row["Final_Energy"]) for row in data]
loss = [float(row["Energy_Loss"]) for row in data]

# Figure 1: Energy Loss Distribution
plt.figure(figsize=(8, 5))
plt.hist(loss, bins=30, edgecolor="black")
plt.xlabel("Energy Loss (MeV)")
plt.ylabel("Number of Neutrons")
plt.title("Neutron Energy Loss Distribution in B4C")
plt.grid(alpha=0.3)
plt.tight_layout()
plt.savefig("energy_loss_distribution.png", dpi=300)
plt.close()

# Figure 2: Initial vs Final Energy
plt.figure(figsize=(8, 5))
plt.scatter(initial, final, alpha=0.6)
plt.xlabel("Initial Energy (MeV)")
plt.ylabel("Final Energy (MeV)")
plt.title("Initial vs Final Neutron Energy")
plt.grid(alpha=0.3)
plt.tight_layout()
plt.savefig("initial_vs_final_energy.png", dpi=300)
plt.close()

print("Both graphs created successfully!")

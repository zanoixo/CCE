import matplotlib

# Use a non-GUI backend.
# This prevents GTK/Wayland-related crashes when generating files.
matplotlib.use("Agg")

import matplotlib.pyplot as plt


# ─────────────────────────────────────────────────────────────────────────────
# DATA — enter your results here
# ─────────────────────────────────────────────────────────────────────────────

elo = [2300, 2400, 2500]

wins   = [48, 34, 23]
draws  = [8, 11, 20]
losses = [44, 55, 57]

# ─────────────────────────────────────────────────────────────────────────────
# CALCULATE TOTAL GAMES
# ─────────────────────────────────────────────────────────────────────────────

games = [
    w + d + l
    for w, d, l in zip(wins, draws, losses)
]


# ─────────────────────────────────────────────────────────────────────────────
# GRAPH 1 — INDIVIDUAL W/D/L GRAPHS
# ─────────────────────────────────────────────────────────────────────────────

for sf_elo, w, d, l, total in zip(elo, wins, draws, losses, games):

    results_pct = [
        w / total * 100,
        d / total * 100,
        l / total * 100
    ]

    labels = ["Zmage", "Remiji", "Porazi"]

    fig, ax = plt.subplots(figsize=(8, 6))

    bars = ax.bar(labels, results_pct)

    ax.set_xlabel("Rezultati")
    ax.set_ylabel("%")
    ax.set_title(f"CCE rezultati proti programu Stockfish 18 {sf_elo}")

    # Y-axis from 0 to 100
    ax.set_ylim(0, 100)

    ax.grid(axis="y", alpha=0.3)

    # Show percentage above each bar
    for bar, percentage in zip(bars, results_pct):
        ax.text(
            bar.get_x() + bar.get_width() / 2,
            percentage + 2,
            f"{percentage:.1f}%",
            ha="center"
        )

    fig.tight_layout()

    # Save as SVG vector graphic
    fig.savefig(
        f"results_sf{sf_elo}.pdf",
        format="pdf"
    )

    # Explicitly close the figure
    plt.close(fig)

    print(f"Generated results_sf{sf_elo}.pdf")


# ─────────────────────────────────────────────────────────────────────────────
# GRAPH 2 — WIN RATE VS STOCKFISH ELO
# ─────────────────────────────────────────────────────────────────────────────

# Chess score:
# Win  = 1 point
# Draw = 0.5 points
# Loss = 0 points

winrate = [
    (w + d * 0.5) / total * 100
    for w, d, total in zip(wins, draws, games)
]


fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(
    elo,
    winrate,
    marker="o",
    linewidth=2
)

ax.axhline(
    y=50,
    linestyle="--",
    linewidth=1.5,
    label="50 %"
)

ax.set_xlabel("Moč programa Stockfish")
ax.set_ylabel("Delež točk")
ax.set_title("CCE Delež točk proti programu Stockfish")

# Y-axis from 0 to 100
ax.set_ylim(0, 100)

ax.grid(True, alpha=0.3)

fig.tight_layout()

# Save as SVG vector graphic
fig.savefig(
    "winrate_vs_elo.pdf",
    format="pdf"
)

plt.close(fig)

print("Generated winrate_vs_elo.svg")
print("Done.")
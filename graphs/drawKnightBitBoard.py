import matplotlib
matplotlib.use("Agg")

import matplotlib.pyplot as plt


# ─────────────────────────────────────────────────────────────────────────────
# CONFIGURATION
# ─────────────────────────────────────────────────────────────────────────────

# Knight positions.
# Use standard chess notation.
KNIGHT_SQUARES = ["c3", "f6"]

# Output file
OUTPUT_FILE = "knight_bitboard.pdf"


# ─────────────────────────────────────────────────────────────────────────────
# BITBOARD
# ─────────────────────────────────────────────────────────────────────────────

def square_to_bit(square):
    """
    Convert a chess square to a bitboard bit index.

    a1 = bit 0
    b1 = bit 1
    ...
    h1 = bit 7
    a2 = bit 8
    ...
    h8 = bit 63
    """

    file = ord(square[0]) - ord("a")
    rank = int(square[1]) - 1

    return rank * 8 + file


# Create bitboard
bitboard = 0

for square in KNIGHT_SQUARES:
    bit = square_to_bit(square)
    bitboard |= 1 << bit


# ─────────────────────────────────────────────────────────────────────────────
# PRINT BITBOARD INFORMATION
# ─────────────────────────────────────────────────────────────────────────────

print("Knight positions:", KNIGHT_SQUARES)

print()
print("Bitboard:")
print(f"{bitboard:064b}")

print()
print("Bitboard (hexadecimal):")
print(f"0x{bitboard:016X}")

print()
print("Bitboard representation:")

for rank in range(7, -1, -1):
    row = []

    for file in range(8):
        bit = rank * 8 + file
        row.append("1" if (bitboard >> bit) & 1 else "0")

    print(" ".join(row))


# ─────────────────────────────────────────────────────────────────────────────
# DRAW CHESSBOARD
# ─────────────────────────────────────────────────────────────────────────────

fig, ax = plt.subplots(figsize=(9, 9))

# Draw squares
for rank in range(8):
    for file in range(8):

        # Alternating chessboard colors
        if (rank + file) % 2 == 0:
            square_color = "#F0D9B5"
        else:
            square_color = "#B58863"

        rectangle = plt.Rectangle(
            (file, rank),
            1,
            1,
            facecolor=square_color,
            edgecolor="black",
            linewidth=1
        )

        ax.add_patch(rectangle)


# ─────────────────────────────────────────────────────────────────────────────
# DRAW BITBOARD VALUES
# ─────────────────────────────────────────────────────────────────────────────

for rank in range(8):
    for file in range(8):

        bit = rank * 8 + file

        value = (bitboard >> bit) & 1

        # Center of square
        x = file + 0.5
        y = rank + 0.5

        ax.text(
            x,
            y,
            str(value),
            ha="center",
            va="center",
            fontsize=24,
            fontweight="bold",
            color="black"
        )


# ─────────────────────────────────────────────────────────────────────────────
# DRAW KNIGHTS
# ─────────────────────────────────────────────────────────────────────────────

for square in KNIGHT_SQUARES:

    file = ord(square[0]) - ord("a")
    rank = int(square[1]) - 1

    ax.text(
        file + 0.5,
        rank + 0.5,
        "   ♞",
        ha="center",
        va="center",
        fontsize=45,
        color="black"
    )


# ─────────────────────────────────────────────────────────────────────────────
# BOARD LABELS
# ─────────────────────────────────────────────────────────────────────────────

ax.set_xticks([i + 0.5 for i in range(8)])
ax.set_xticklabels(["a", "b", "c", "d", "e", "f", "g", "h"], fontsize=14)

ax.set_yticks([i + 0.5 for i in range(8)])
ax.set_yticklabels(["1", "2", "3", "4", "5", "6", "7", "8"], fontsize=14)

ax.tick_params(
    axis="both",
    which="both",
    length=0
)


# ─────────────────────────────────────────────────────────────────────────────
# TITLE
# ─────────────────────────────────────────────────────────────────────────────

ax.set_title(
    "Bitboard Representation of Knights",
    fontsize=20,
    pad=20
)


# Keep board square
ax.set_xlim(0, 8)
ax.set_ylim(0, 8)
ax.set_aspect("equal")

plt.tight_layout()

# Save as SVG (vector graphics)
plt.savefig(
    OUTPUT_FILE,
    format="pdf",
    bbox_inches="tight"
)

plt.close()

print()
print(f"Generated: {OUTPUT_FILE}")
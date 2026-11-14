import sys

# averages every STOPTIMING label in a log and counts the timed pairs nested one level inside it
times = {}
inner = {}
stack = []

for line in open(sys.argv[1]):
    depth = line.count("| ")
    text = line[depth * 2:].strip()
    if text.startswith("STARTTIMING: "):
        stack.append(0)
    elif text.startswith("STOPTIMING: "):
        label, ms = text[len("STOPTIMING: "):].rsplit(" ", 1)
        times.setdefault(label, []).append(float(ms[:-2]))
        inner.setdefault(label, []).append(stack.pop())
        if stack:
            stack[-1] += 1

print("%-40s %6s %12s %12s %12s %12s" % ("label", "count", "avg ms", "min ms", "max ms", "avg inner"))
for label in times:
    t = times[label]
    c = inner[label]
    print("%-40s %6d %12.4f %12.4f %12.4f %12.1f" % (label, len(t), sum(t) / len(t), min(t), max(t), sum(c) / len(c)))

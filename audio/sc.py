import soundcard as sc

speakers = sc.all_speakers()
mics = sc.all_microphones(include_loopback=True)

print(speakers)
print(mics)

s = speakers[0]
m = mics[2]
print(s)
print(m)

def is_silent(data):
    for d in data:
        if abs(d[0]) > 0.05 or abs(d[1] > 0.05):
            return False
    return True

with m.recorder(samplerate=48000, blocksize=512) as mic, s.player(samplerate=48000, blocksize=512) as sp:
    print("starting")
    for _ in range(10000):
        data = mic.record(numframes=256)
#        print(data)
#        print(is_silent(data))
#        print("record -> play")
        sp.play(data)

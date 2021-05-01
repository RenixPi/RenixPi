import pyaudio
import wave
import time
import struct
import math

form_1 = pyaudio.paInt16 # 16-bit resolution
chans = 1 # 1 channel
samp_rate = int(44100/4) # 44.1kHz sampling rate
chunk = 4096 # 2^12 samples for buffer
record_secs = 3 # seconds to record
dev_index = 2 # device index found by p.get_device_info_by_index(ii)
wav_output_filename = 'test1.wav' # name of .wav file

audio = pyaudio.PyAudio() # create pyaudio instantiation


SHORT_NORMALIZE = (1.0/32768.0)
swidth = 2

def rms(frame):
    count = len(frame) / swidth
    format = "%dh" % (count)
    shorts = struct.unpack(format, frame)

    sum_squares = 0.0
    for sample in shorts:
        n = sample * SHORT_NORMALIZE
        sum_squares += n * n
    rms = math.pow(sum_squares / count, 0.5)

    return rms * 1000


def callback(in_data, frame_count, time_info, status):
    print("rms {}".format(rms(in_data)))
    return (in_data, pyaudio.paContinue)




# create pyaudio stream
stream = audio.open(format = pyaudio.paFloat32,
  rate = samp_rate,
  channels = chans,
  input_device_index = dev_index,
  input = True,
  output = True,
  frames_per_buffer=8192,
  stream_callback=callback)


stream.start_stream()
while stream.is_active():
    time.sleep(0.5)

stream.stop_stream()
stream.close()

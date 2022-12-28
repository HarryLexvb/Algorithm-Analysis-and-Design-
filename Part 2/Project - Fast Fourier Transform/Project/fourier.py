# -*- coding: utf-8 -*-
"""Fourier.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1sKh3H0djDup9lWXAgv9c0V3vQbn4gi77
"""

from google.colab import drive
drive.mount('/content/drive')

"""#***Fourier Transform***"""

import numpy as np
import librosa 
import librosa.display

import matplotlib.pyplot as plt

from IPython.display import Audio

"""##Ejemplo simple de FFT

"""

samples   = 100
f         = 3
x         = np.arange(samples)
y1        = np.sin(2*np.pi*f*(x/samples))
plt.figure()
plt.stem(x,y1,'r')
plt.plot(x,y1)
plt.xlabel('Tiempo ----->')
plt.ylabel('<<<<   amplitud   >>>>')
plt.show()

import scipy

def fft_plot(audio, sampling_rate):
  n   = len(audio)
  T   = 1/sampling_rate
  yf  = scipy.fft.fft(audio)
  
  xf  = np.linspace(0.0, 1.0/(2.0*T), int(n/2))
  fig, ax = plt.subplots()
  ax.plot(xf, 2.0/n * np.abs(yf[:n//2]))
  plt.grid()
  plt.xlabel('Frecuencia ->->')
  plt.ylabel('Magnitude')
  return plt.show()

fft_plot(y1, 100)

"""---"""

import soundfile as sf

ruta  = '/content/drive/MyDrive/Colab Notebooks/'
vfile = ruta + 'voz.wav'
out   = ruta + 'out.wav'

y, sr = librosa.load(vfile)
print(y)

duration = len(y)/sr
print(duration)

sf.write(out, y, sr)

plt.figure()
librosa.display.waveshow(y=y,sr=sr)
plt.xlabel('Tiempo en segundos -->')
plt.ylabel('Amplitud')
plt.show()

Audio(out)

"""En esta visualización podemos apreciar la información de la voz en un representación en el dominio del tiempo. La amplitud de las ondas representa el sonido. Sin embargo, la información no es clara. Para ello se puede realizar una transformación a un espacio que permita definir patrones que ayuden en la comprensión de la información.

"""

fft_plot(y1, 100)

fft_plot(y,sr)

import scipy

def fft_plot_2(audio, sampling_rate):
  n   = len(audio)
  T   = 1/sampling_rate
  yf  = scipy.fft.fft(audio)

 
 
  yf2 = np.convolve(yf, [-0.01,2.1,-0.01])
 
  xf  = np.linspace(0.0, 1.0/(2.0*T), int(n/2))
  fig, ax = plt.subplots()
  ax.plot(xf, 2.0/n * np.abs(yf2[:n//2]))
  plt.grid()
  plt.xlabel('Frecuencia ->->')
  plt.ylabel('Magnitude')
  plt.show()
  return yf2

y=fft_plot_2(y1, 100)

import soundfile as sf

ruta  = '/content/drive/MyDrive/Colab Notebooks/'
vfile = ruta + 'voz.wav'
out   = ruta + 'out.wav'

y, sr = librosa.load(vfile)
print(y)

duration = len(y)/sr
print(duration)

sf.write(out, y, sr)

yf2 = fft_plot_2(y,sr)

iy  = scipy.fft.ifft(yf2)

sf.write(out, np.abs(iy), sr)

Audio(out)
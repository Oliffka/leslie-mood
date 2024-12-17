# Leslie Mood - Leslie Speaker Effect Audio Plugin

This project involves the development of an audio plugin that emulates the sound of a Leslie speaker. This rotary speaker system produces a rich and distinctive sound, characterized by amplitude and frequency modulation effects due to the rotating components. Additionally, the system introduces some distortion from the amplifier and complex reflections caused by the cabinet's design.

<img src="/Images/leslie.png" alt="The Leslie cabinet" style="width:40%; height:auto;">

The current implementation explores two approaches to simulate this effect: signal processing approach and black-box modelling using deep learning techniques.

# Signal Processing approach
This approach is based on time-varying spectral delay filters producing a pleasant sound effect. This technique applies a frequency-dependent delay to the audio signal, imitating the Doppler effect caused by the rotating speaker components. This implementation is based on the research from [Computationally efficient hammond organ synthesis](https://www.dafx.de/paper-archive/2011/Papers/49_e.pdf), providing a computationally efficient simulation of the Leslie speaker effect.


# DL approach (Work in Progress)
This implementation explores black-box modelling of the Leslie speaker effect using deep learning techniques. This method is currently under research to identify the most suitable neural network architecture capable of reproducing the complex characteristics of the Leslie speaker effect.

This approach assumes having a dataset comprising of Original audio (dry signal) and Processed audio (Leslie speaker sound). The goal is to train a model to learn the mapping between the dry and processed audio, capturing all the mentioned nuances. Some ideas are inspired by the findings in the [Deep Learning for Black-Box Modeling of Audio Effects](https://www.mdpi.com/2076-3417/10/2/638) article.

# How to Use and Demo Video

In the Release folder, you will find both VST3 and AU versions of the plugin. Additionally, there is a demo video, providing a brief explanation and demonstration of how to use the plugin: [Leslie Mood Demo](https://youtu.be/jNPVKuDq5Us).

The plugin is built and tested on macOS.

<img src="/Images/leslie_mood.png" alt="The Leslie cabinet" style="width:40%; height:auto;">

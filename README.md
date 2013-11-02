A chord finder for the Korg EMX-1
=================================

<img src="http://www.korg.com/uploads/Products/Product_Images/EMXSD_TOP_MAIN_634051071289310000.png" width="100%"/>

The Korg EMX-1 has a chord oscillator which can stack two (or three) independent voices on top of a root note to form a chord. The chord configuration can be selected from a built-in list (major, minor, dim, aug7, M7, sus4, etc.)

My problem was that it's not easy to find out which chords can be built on top of the notes of a scale so that the resulting chords are consonant (its notes remain within the scale).

This small app was written to scratch this itch.

With this app, you can:

1. set the root note of your scale (C, C#, D, ..., Bb, B)

2. select the type of the scale (Ionian, Dorian, Gypsy, Blues, ...): this specifies how many semitones to advance at each degree when building the scale

3. set a mode: with this you can shift the scale steps, for instance the major scale 2-2-1-2-2-2-1 with mode 2 becomes 1-2-2-2-1-2-2

After making your selection, you can see the notes of the resulting scale and all chords which can be safely built on top of the various notes.

If you click on a chord name, the program sends noteon commands (in FluidSynth command language) to standard output. If you pipe stdout to fluidsynth, you can hear the chords in your favorite soundfont. See the `play` target in the Makefile for an example.

Dependencies:

* FLTK
* FluidSynth (only if you want to try your chords)

Note: the EMX chord definitions have not been verified yet, so there may be bugs (chord configurations on the EMX may not match what is shown in and played by the app).

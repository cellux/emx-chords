CXX      = $(shell fltk-config --cxx)
DEBUG    = -g
CXXFLAGS = $(shell fltk-config --cxxflags) -I.
LDFLAGS  = $(shell fltk-config --ldflags)
LINK     = $(CXX)

TARGET = emx-chords
OBJS = emx-chords.o
SRCS = emx-chords.cxx

.SUFFIXES: .o .cxx
%.o: %.cxx
	$(CXX) $(CXXFLAGS) $(DEBUG) -c $<

$(TARGET): $(OBJS)
	$(LINK) -o $(TARGET) $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o 2> /dev/null
	rm -f $(TARGET) 2> /dev/null

.PHONY: play
play:
	./$(TARGET) | fluidsynth --no-midi-in -a alsa /usr/share/soundfonts/fluidr3/FluidR3GM.SF2

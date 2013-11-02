#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Dial.H>
#include <FL/fl_draw.H>

static const char *APP_NAME = "emx-chords";

static const int MIDI_MIDDLE_C = 60;

static const char* scaleData[] = {
  // from http://www.pluck-n-play.com/en/scale-list.html
  //
  // sharps and flats are relative to the corresponding degree of the
  // major scale

  // Major and Natural Minor
  "Ionian",
    "1-2-3-4-5-6-7",
  "Dorian",
    "1-2-b3-4-5-6-b7",
  "Phrygian",
    "1-b2-b3-4-5-b6-b7",
  "Lydian",
    "1-2-3-#4-5-6-7",
  "Mixolydian",
    "1-2-3-4-5-6-b7",
  "Aeolian",
    "1-2-b3-4-5-b6-b7",
  "Locrian",
    "1-b2-b3-4-b5-b6-b7",

  // Harmonic Minor
  "Aeolian 7",
    "1-2-b3-4-5-b6-7",
  "Locrian 6",
    "1-b2-b3-4-b5-6-b7",
  "Ionian #5",
    "1-2-3-4-#5-6-7",
  "Dorian #4",
    "1-2-b3-#4-5-6-b7",
  "Phrygian 3",
    "1-b2-3-4-5-b6-b7",
  "Lydian #2",
    "1-#2-3-#4-5-6-7",
  "Locrian b4 bb7",
    "1-b2-b3-b4-b5-b6-bb7",

  // Melodic Minor
  "Aeolian 6 7",
    "1-2-b3-4-5-6-7",
  "Phrygian 6",
    "1-b2-b3-4-5-6-b7",
  "Lydian #5",
    "1-2-3-#4-#5-6-7",
  "Lydian b7",
    "1-2-3-#4-5-6-b7",
  "Aeolian 3",
    "1-2-3-4-5-b6-b7",
  "Locrian 2",
    "1-2-b3-4-b5-b6-b7",
  "Locrian b4",
    "1-b2-b3-b4-b5-b6-b7",

  // Bebop
  "Bebop Dominant",
    "1-2-3-4-5-6-#6-7",
  "Bebop Major",
    "1-2-3-4-5-b6-6-7",
  "Bebop Minor",
    "1-2-b3-3-4-5-6-b7",
  "Bebop Melodic Minor",
    "1-2-b3-4-5-b6-6-7",

  // Blues
  "Blues Major",
    "1-2-b3-3-5-6",
  "Blues Minor",
    "1-b3-4-b5-5-b7",
  "Blues Diminished",
    "1-b2-b3-3-b5-5-6-b7",
  "Blues Pentatonic",
    "1-b3-4-5-b7",
  "Blues Rock'n'Roll",
    "1-2-b3-3-4-b5-5-6-b7",

  // Gypsy
  "Gypsy Major",
    "1-b2-3-4-5-b6-7",
  "Gypsy Minor",
    "1-2-b3-b5-5-b6-7",
  "Hungarian Gypsy",
    "1-2-b3-#4-5-b6-b7",
  "Spanish Gypsy",
    "1-b2-3-4-5-b6-b7",

  // Pentatonics
  "Major Pentatonic",
    "1-2-3-5-6",
  "Neutral Pentatonic",
    "1-2-4-5-b7",
  "Rock Pentatonic",
    "1-b3-4-#5-b7",
  "Scottish Pentatonic",
    "1-2-4-5-6",
  "Minor Pentatonic",
    "1-b3-4-5-b7",

  // Whole-Half
  "Whole",
    "1-2-3-#4-#5-#6",
  "Whole-Half",
    "1-2-b3-4-#4-#5-6-7",
  "Half-Whole",
    "1-b2-b3-3-b5-5-6-b7",

  // Other
  "Augmented",
    "1-#2-3-5-#5-7",
  "Byzantine",
    "1-b2-3-4-5-b6-7",
  "Chromatic",
    "1-#1-2-#2-3-4-#4-5-#5-6-#6-7",
  "Enigmatic (ascending)",
    "1-b2-3-#4-#5-#6-7",
  "Enigmatic (descending)",
    "1-b2-3-4-b6-b7-7",
  "Hungarian Major",
    "1-b3-3-b5-5-6-b7",
  "Hungarian Minor",
    "1-2-b3-b5-5-b6-7",
  "Neapolitan Major",
    "1-b2-b3-4-5-6-7",
  "Neapolitan Minor",
    "1-b2-b3-4-5-b6-7",
  "Overtone",
    "1-2-3-#4-5-6-b7",
  "Prometheus",
    "1-2-3-b5-6-b7",
  "Prometheus Neapolitan",
    "1-b2-3-b5-6-b7",
  "Spanish 8 Tone",
    "1-b2-b3-3-4-b5-b6-b7",

  NULL
};

static const char *chordData[] = {
  "major", "1-3-5",
  "6th", "1-3-5-6",
  "7th", "1-3-5-7",
  "M7", "1-3-5-7",
  "m7b5", "1-b3-b5-b7",
  "minor", "1-b3-5",
  "m6", "1-b3-5-6",
  "m7", "1-b3-5-b7",
  "mMaj7", "1-b3-5-7",
  "dim", "1-b3-b5",
  "dim7", "1-b3-b5-bb7",
  "m7b5", "1-b3-b5-b7",
  "aug", "1-3-#5",
  "aug7", "1-3-#5-7",
  "sus4", "1-4-5",
  "sus7", "1-4-5-7",
  NULL
};

// ScaleID is a bit-pattern uniquely identifying a given scale
//
// each bit corresponds to a distance from the tonic in semitones
//
// if a bit is set, it means the corresponding note is a member of the
// scale
//
// bit 0 corresponds to the tonic and is always 1
//
// example: the ScaleID of the major scale is 101010110101
typedef unsigned short ScaleID;

class Scale {
  ScaleID sid_;
  const char *name_;

  static ScaleID parseDescriptor(const char *descriptor) {
    static int majorScaleOffsets[] = { 0,2,4,5,7,9,11 };
    ScaleID result = 0;
    const char *start = descriptor;
    while (*start) {
      // search for next delimiter (-) or the end of string
      const char *end = start;
      while (*end!='-' && *end!=0) ++end;
      // the last digit is the major scale degree
      int offset = majorScaleOffsets[*(end-1)-'1'];
      // possible modifying prefixes are b, bb and #
      if (*start=='b') {
        --offset;
        if ((start+1<end-1) && *(start+1)=='b') {
          --offset;
        }
      }
      else if (*start=='#') {
        ++offset;
      }
      result |= 1<<offset;
      start = end;
      // skip delimiter (-)
      if (*start=='-') ++start;
    }
    return result;
  }

public:
  Scale(const char *name, const char *descriptor)
    : sid_(parseDescriptor(descriptor)),
      name_(name) {}

  const char *name() { return name_; }

  /* list of note distances from the tonic, in semitones */
  std::vector<int> offsets() {
    std::vector<int> result;
    for (int i=0; i<12; i++) {
      if (sid_ & (1<<i)) {
        result.push_back(i);
      }
    }
    return result;
  }

  /* list of distances between successive notes */
  std::vector<int> steps() {
    std::vector<int> result;
    int last = 0;
    for (int i=1; i<12; i++) {
      if (sid_ & (1<<i)) {
        result.push_back(i-last);
        last = i;
      }
    }
    // push last step
    //
    // (which brings us back to the tonic one octave higher)
    result.push_back(12-last);
    return result;
  }

  /* number of notes in the scale */
  int nDegrees() {
    return offsets().size();
  }

  /* list of notes (semitone offsets) comprising the scale
   *
   * the notes start at `root' and increase with the scale's steps
   *
   * if `mode' is given, then the list of steps is shifted (rotated)
   * to the left with `mode' positions
   */
  std::vector<int> notes(int root=0, int mode=0) {
    std::vector<int> s = steps();
    std::vector<int> result;
    int note = root;
    for (int i=0; i<s.size(); i++) {
      result.push_back(note);
      note += s[(mode+i)%s.size()];
    }
    return result;
  }

  /* print the scale to standard error */
  void print() {
    std::cerr << "Scale: " << name_ << "\n";
    std::cerr << "  sid=" << sid_ << "\n";
    std::cerr << "  nDegrees=" << nDegrees() << "\n";
    std::cerr << "  offsets=[";
    std::vector<int> o = offsets();
    for (int i=0; i<o.size(); i++) {
      std::cerr << o[i];
      if (i<o.size()-1) {
        std::cerr << "-";
      }
    }
    std::cerr << "]\n";
    std::cerr << "  steps=[";
    std::vector<int> s = steps();
    for (int i=0; i<s.size(); i++) {
      std::cerr << s[i];
      if (i<s.size()-1) {
        std::cerr << "-";
      }
    }
    std::cerr << "]\n";
  }
};

static std::vector<std::string> notes;

static void initNotes() {
  notes.push_back("C");
  notes.push_back("C#");
  notes.push_back("D");
  notes.push_back("D#");
  notes.push_back("E");
  notes.push_back("F");
  notes.push_back("F#");
  notes.push_back("G");
  notes.push_back("G#");
  notes.push_back("A");
  notes.push_back("Bb");
  notes.push_back("B");
}

/* convert a midi note number to the corresponding note name */
const char *midiNote(int note) {
  return notes[(note-MIDI_MIDDLE_C)%12].c_str();
}

static void parseScaleData(const char **data, std::vector<Scale> &target) {
  while (*data) {
    const char *name = data[0];
    const char *descriptor = data[1];
    Scale s(name, descriptor);
    //s.print();
    target.push_back(s);
    data += 2;
  }
}

static std::vector<Scale> scales;
static std::vector<Scale> chords;

class ScaleInfoWidget : public Fl_Widget {
  int root_;
  Scale *scale_;
  int mode_;
  int nDegrees_;
  std::vector<int> steps_;
  std::vector<int> notes_;
  std::vector< std::vector<Scale> > noteChords_;
  int mousex_, mousey_; // -1 if outside the widget
  int iCurrentNote_, iCurrentChord_;
public:
  ScaleInfoWidget(int x, int y, int w, int h)
    : Fl_Widget(x, y, w, h),
      root_(0), scale_(0), mode_(0), nDegrees_(0),
      mousex_(-1), mousey_(-1),
      iCurrentNote_(-1), iCurrentChord_(-1)
  {}
  void scale(Scale &s) { scale_ = &s; }
  void root(int r) { root_ = r; }
  void mode(int m) { mode_ = m; }
  void recalc() {
    nDegrees_ = scale_->nDegrees();
    steps_ = scale_->steps();
    notes_ = scale_->notes(root_, mode_);
    noteChords_.clear();
    for (int i=0; i<notes_.size(); i++) {
      std::vector<Scale> noteChords;
      for (int j=0; j<chords.size(); j++) {
        std::vector<int> chordNotes = chords[j].notes(notes_[i]);
        int k;
        for (k=0; k<chordNotes.size(); k++) {
          // move it back to the octave if necessary
          int n = root_ + (chordNotes[k] - root_) % 12;
          if (std::find(notes_.begin(),notes_.end(), n)==notes_.end()) {
            break;
          }
        }
        if (k==chordNotes.size()) {
          noteChords.push_back(chords[j]);
        }
      }
      noteChords_.push_back(noteChords);
    }
  }
  void draw() {
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());
    fl_color(FL_FOREGROUND_COLOR);
    fl_font(0, 16);
    int em = fl_width("M");
    int nw = w()/(nDegrees_*2);
    char stepstr[16];
    for (int i=0; i<steps_.size(); i++) {
      sprintf(stepstr, "%d", steps_[i]);
      fl_draw(stepstr, x()+nw*(i+1)-em, y()+em, 2*em, em, FL_ALIGN_CENTER);
    }
    for (int i=0; i<steps_.size()-1; i++) {
      sprintf(stepstr, "%d", steps_[i]);
      fl_draw(stepstr, x()+nw*(steps_.size()+i+1)-em, y()+em, 2*em, em, FL_ALIGN_CENTER);
    }
    iCurrentNote_ = -1;
    iCurrentChord_ = -1;
    for (int i=0; i<notes_.size(); i++) {
      fl_font(0,16);
      fl_draw(midiNote(MIDI_MIDDLE_C+notes_[i]), x()+nw*(mode_+i)+nw/2-em, y()+3*em, 2*em, em, FL_ALIGN_CENTER);
      int cy = y()+5*em;
      std::vector<Scale> noteChords = noteChords_[i];
      for (int j=0; j<noteChords.size(); j++) {
        int left = x()+nw*(mode_+i);
        int right = left+nw;
        int top = cy;
        int bottom = top+em;
        if (mousex_ > left && mousex_ < right && mousey_ > top && mousey_ < bottom) {
          fl_font(1,12);
          iCurrentNote_ = i;
          iCurrentChord_ = j;
        }
        else {
          fl_font(0,12);
        }
        fl_draw(noteChords[j].name(), left+nw/2-em, top, 2*em, em, FL_ALIGN_CENTER);
        cy += 2*em;
      }
    }
  }
  int handle(int event) {
    switch (event) {
    case FL_ENTER:
    case FL_MOVE:
      mousex_ = Fl::event_x();
      mousey_ = Fl::event_y();
      redraw();
      //std::cerr << "mousex=" << mousex_ << ",mousey=" << mousey_ << "\n";
      return 1;
    case FL_LEAVE:
      mousex_ = -1;
      mousey_ = -1;
      return 1;
    case FL_PUSH:
      if (iCurrentNote_ >= 0 && iCurrentChord_ >= 0) {
        Scale &s = noteChords_[iCurrentNote_][iCurrentChord_];
        std::vector<int> chordNotes = s.notes(notes_[iCurrentNote_]);
        for (int i=0; i<chordNotes.size(); i++) {
          std::cout << "noteon 1 " << (MIDI_MIDDLE_C+chordNotes[i]) << " 127\n";
        }
        std::cout.flush();
      }
      return 1;
    }
    return Fl_Widget::handle(event);
  }
};

class MainWindow : public Fl_Double_Window {
  Fl_Dial *rootDial_;
  Fl_Box *rootBox_;
  Fl_Dial *scaleDial_;
  Fl_Box *scaleBox_;
  Fl_Dial *modeDial_;
  Fl_Box *modeBox_;
  ScaleInfoWidget *scaleInfoWidget_;

  static void cbDialChanged(Fl_Widget *widget, void *data) {
    MainWindow *mw = (MainWindow*) data;
    mw->onDialChanged((Fl_Dial*) widget);
    mw->redraw();
  }
  void onDialChanged(Fl_Dial *dial) {
    if (dial==rootDial_) {
      rootBox_->label(notes[rootDial_->value()].c_str());
      scaleInfoWidget_->root(rootDial_->value());
    }
    else if (dial==scaleDial_) {
      Scale &s = scales[scaleDial_->value()];
      modeDial_->range(0, s.nDegrees()-1);
      modeDial_->value(0);
      scaleBox_->label(s.name());
      scaleInfoWidget_->scale(s);
    }
    std::ostringstream s;
    s << modeDial_->value();
    modeBox_->copy_label(s.str().c_str());
    scaleInfoWidget_->mode(modeDial_->value());
    scaleInfoWidget_->recalc();
  }

public:
  MainWindow(int w, int h)
    : Fl_Double_Window(w, h)
  {
    label(APP_NAME);
    fl_font(0,24);
    int em = fl_width("M");
    int dialw = em*4;
    int x = 0.5*(w/3);
    rootDial_ = new Fl_Dial(x-dialw/2,em,dialw,dialw,"Root");
    rootDial_->range(0,11);
    rootDial_->step(1);
    rootDial_->callback(cbDialChanged, this);
    rootDial_->when(FL_WHEN_CHANGED);
    rootDial_->labelsize(12);
    rootBox_ = new Fl_Box(FL_SHADOW_FRAME, x-2*em,em+dialw+em,4*em,em,notes[0].c_str());
    rootBox_->labelsize(16);
    x = 1.5*(w/3);
    scaleDial_ = new Fl_Dial(x-dialw/2,em,dialw,dialw,"Scale");
    scaleDial_->range(0,scales.size()-1);
    scaleDial_->step(1);
    scaleDial_->callback(cbDialChanged, this);
    scaleDial_->when(FL_WHEN_CHANGED);
    scaleDial_->labelsize(12);
    scaleBox_ = new Fl_Box(FL_SHADOW_FRAME, x-5*em,em+dialw+em,10*em,em,scales[0].name());
    scaleBox_->labelsize(16);
    x = 2.5*(w/3);
    modeDial_ = new Fl_Dial(x-dialw/2,em,dialw,dialw,"Mode");
    modeDial_->range(0,scales[0].nDegrees()-1);
    modeDial_->step(1);
    modeDial_->callback(cbDialChanged, this);
    modeDial_->when(FL_WHEN_CHANGED);
    modeDial_->labelsize(12);
    modeBox_ = new Fl_Box(FL_SHADOW_FRAME, x-2*em,em+dialw+em,4*em,em,"0");
    modeBox_->labelsize(16);
    int y = rootBox_->y()+em*2;
    scaleInfoWidget_ = new ScaleInfoWidget(em,y,w-em*2,h-y-em);
    scaleInfoWidget_->scale(scales[0]);
    scaleInfoWidget_->recalc();
    end();
  }
};

int dummyArgParser(int argc, char** argv, int &i) {
  return 0;
}

int main(int argc, char **argv) {
  initNotes();
  parseScaleData(scaleData, scales);
  parseScaleData(chordData, chords);
  MainWindow *window = new MainWindow(1024, 600);
  window->show(argc, argv);
  int status = Fl::run();
  return status;
}

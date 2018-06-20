#define countof(array) (sizeof(array)/sizeof(array[0]))

const uint8_t buzzerPin = 6;

typedef struct {
	char name[3];
	double freq;
} toneFreq_t;

const toneFreq_t toneList[] = {
	{"C",  32.703},
	{"C#", 34.648},
	{"D",  36.708},
	{"D#", 38.891},
	{"E",  41.203},
	{"F",  43.654},
	{"F#", 46.249},
	{"G",  48.999},
	{"G#", 51.913},
	{"A",  55.000},
	{"A#", 58.270},
	{"B",  61.735},
};

typedef struct {
	char name[3];
	unsigned int octave;
	double duration;
} note_t;

const note_t familyMartEntrance[] = {
	{"F#", 5, 0.5},
	{"D",  5, 0.5},
	{"A",  4, 0.5},
	{"D",  5, 0.5},
	{"E",  5, 0.5},
	{"A",  5, 1.5},
	{"E",  5, 0.5},
	{"F#", 5, 0.5},
	{"E",  5, 0.5},
	{"A",  4, 0.5},
	{"D",  5, 1},
	{"",   1, 1}
};

void playNote(note_t note, unsigned long quarterNoteMs) {
	unsigned long durationMs = quarterNoteMs * note.duration;

	for (int i = 0; i < countof(toneList); i++) {
		if (!strncmp(note.name, toneList[i].name, 2)) {
			tone(buzzerPin, (unsigned int)(toneList[i].freq * (1 << (note.octave - 1))));
			delay(durationMs);
			return;
		}
	}

	noTone(buzzerPin);
	delay(durationMs);
}

void playScore(const note_t score[], int scoreLength, unsigned int bpm) {
	unsigned long quarterNoteMs = 60000 / bpm;

	for (int i = 0; i < scoreLength; i++) {
		playNote(score[i], quarterNoteMs);
	}
}

void setup() {

}

void loop() {
	playScore(familyMartEntrance, countof(familyMartEntrance), 80);

	delay(3000);
}

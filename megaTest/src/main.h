void testCommand(const byte * commands);
void debugCpuSpeed(uint16_t noLoop);

void processIncommingSnapMessage();
uint32_t getShiftInData(uint8_t size);
void writeCoil(byte bs, byte size);
void actionDimmer1(byte power1, byte power2);
void onRfReceive(uint8_t * data, size_t size);

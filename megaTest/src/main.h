using SwitchStatesType = uint32_t;

void testCommand(const byte * commands);
void debugCpuSpeed(uint16_t noLoop);

void processIncommingSnapMessage();
uint32_t getShiftInData(uint8_t size);
void writeCoil(byte bs, byte size);
void actionDimmer1Set(uint8_t index, uint8_t powerLvl);
void actionDimmer1Swap(uint8_t index);
void onRfReceive(uint8_t * data, size_t size);
void onSwitchChange(SwitchStatesType states);

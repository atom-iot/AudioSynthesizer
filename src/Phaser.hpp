#pragma once
/*
   Эффект 'ФЕЙЗЕР' (фазовращатель)
   Частный случай ФЛЭНЖЕРа
   Отличие в том, что время задержки определяется динамически
*/
class Phaser {
  public:
    Phaser(uint32_t sampleRate) {
      _delay = new Delay(30000, sampleRate);                                                                            //Задержка
      _osc = new Oscil;
    }
    ~Phaser() {
      delete _delay;
      delete _osc;
    }
    void balance(uint16_t value) {                                                                                      //Баланс wet/dry (смесь обработанного и необработанного сигнала)
      _delay -> balance(value);
    }
    void feedback(uint16_t value) {                                                                                     //Уровень линнии обратной связи
      _delay -> feedback(value);
    }
    void wave(uint8_t waveType, uint16_t waveFreq, uint16_t waveAmpl, uint16_t wavePhase, bool waveDirect = true) {     //Установка параметров волны модулятора
      _osc -> type(waveType);
      if (waveFreq > 3)                                                                                                 //Максимум 3 Гц
        waveFreq = 3;
      _osc -> freq(waveFreq);
      _osc -> ampl(waveAmpl);
      _osc -> phase(wavePhase, waveDirect);
    }
    uint16_t get(uint16_t input, uint16_t freqVal) {                                                                    //Получить обработанный сигнал
      _delay -> delay(map(_osc -> get(), 0, 4095, 0, 1000000 / freqVal));                                               //Устанавливаем задержку по волне (в зависимости от периода сигнала)
      return _delay -> get(input);                                                                                      //Получаем
    }
  private:
    Delay* _delay;
    Oscil* _osc;
};

#ifndef TIME_H
#define TIME_H

class Time {
public:
    static float deltaTime; // İki kare arasındaki fark (saniye)
    static float lastFrame; // Bir önceki karenin zamanı

    static void update();   // Her döngü başında çağrılmalıdır
};

#endif
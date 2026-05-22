#define IGBT1 PD0
#define IGBT2 PD1
#define IGBT3 PD2
#define IGBT4 PD3

void setup() {
    // ضبط الأطراف كمخارج
    DDRD |= (1 << IGBT1) | (1 << IGBT2) | (1 << IGBT3) | (1 << IGBT4);
    
    // بدء تشغيل Timer1 بتردد 50Hz
    TCCR1A = 0; // Normal Mode
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC Mode, Prescaler = 8

    OCR1A = 10000;  // تحديد فترة 10ms (نصف دورة الموجة)
    TIMSK |= (1 << OCIE1A); // تفعيل المقاطعة عند انتهاء العد
}

ISR(TIMER1_COMPA_vect) {
    static bool state = false;
    
    if (state) {
        // تشغيل IGBT1, IGBT4 وإطفاء IGBT2, IGBT3
        PORTD = (1 << IGBT1) | (1 << IGBT4);
    } else {
        // تشغيل IGBT2, IGBT3 وإطفاء IGBT1, IGBT4
        PORTD = (1 << IGBT2) | (1 << IGBT3);
    }
    
    state = !state; // عكس الحالة في كل مقاطعة
}

void loop() {
    // لا يوجد شيء هنا لأن التحكم يتم عبر الـ ISR
}
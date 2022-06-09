bool just_published = false;
int publish_count = 0;

void setup() {
    pinMode(D2, INPUT);
    
    // wait 2 minutes before motion detection is allowed
    // so user does not set off device by acident
    delay(120 * 1000);
}

void loop() {

    // wait 5 mins before publishing again
    // can only publish 3 times, so not to clog users inbox
    if (just_published == true and publish_count < 3)
    {
        delay(5 * 60 * 1000);
        just_published = false;
    }
    
    // if motion is detected publish event to trigger email being sent
    if (digitalRead(D2) == HIGH and just_published == false)
    {
        // delay of 1 minute to give user time to turn off device
        delay(60 * 1000);
        Particle.publish("event", "triggered", PUBLIC);
        just_published = true;
        publish_count += 1;
    }
    
}

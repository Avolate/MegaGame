package com.FlyingDangerJava.Main;

import com.badlogic.gdx.backends.lwjgl3.Lwjgl3Application;
import com.badlogic.gdx.backends.lwjgl3.Lwjgl3ApplicationConfiguration;
import com.flyingdanger.main;

public class DesktopLauncher {
    public static void Main(String[] args) {
        Lwjgl3ApplicationConfiguration config = new Lwjgl3ApplicationConfiguration();
        config.setTitle("Flying Danger");
        config.setWindowedMode(1280, 720);
        new Lwjgl3Application(new Main(), config);
    }
}

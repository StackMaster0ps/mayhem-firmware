# 📡 Recon Ping Detector App (for HackRF/PortaPack Mayhem)

**A tactical utility for detecting and responding to active RF triangulation attempts.**

---

## 🚩 App Features

- **Passive Scanning:** Detects periodic RF ping signals.
- **Manual Direction Finding:** Assists users in identifying signal direction.
- **PANIC Mode:** Records environmental audio, intercepts active comms, and replays intercepted transmissions.

---

## 📸 UI Mockups

### 🎯 Main Scanning Screen

```plaintext
───────────────────────────────────────
| 🔍 Recon Ping Detector              |
───────────────────────────────────────
|                                     |
| Frequency Range:  [ 2.4 GHz ▼ ]     |
|                                     |
| [ Start Scan ]      [ Settings ⚙️ ] |
|                                     |
| ┌───────────────────────────┐       |
| │      RSSI Strength        │       |
| │   ┌───────────────────┐   │       |
| │   │███████            │   │       |
| │   └───────────────────┘   │       |
| └───────────────────────────┘       |
|                                     |
| ┌───────────────────────────┐       |
| │     Spectrum Waterfall    │       |
| │ █▂▃▁▃▅▃▂▁▂▃▅▆▅▃▁▂▂▃▅▃▂█   │       |
| │ █▃▅▃▂▁▂▃▅▆▅▃▁▂▂▃▅▃▂▂▂█   │       |
| └───────────────────────────┘       |
|                                     |
───────────────────────────────────────
```

---

### 🚨 Ping Detection Alert

```plaintext
───────────────────────────────────────
| 🚨 RF Ping Detected!                |
───────────────────────────────────────
|                                     |
| Frequency:        [ 2.437 GHz ]     |
| Signal Strength:  [ -40 dBm  ]      |
| Interval:         [ 5 sec    ]      |
|                                     |
| ┌───────────────────────────┐       |
| │       Direction Assist    │       |
| │                           │       |
| │           ▲ N             │       |
| │           │               │       |
| │       ◀───○───▶           │       |
| │           │               │       |
| │           ▼ S             │       |
| │    Rotate antenna to      │       |
| │  align peak RSSI strength │       |
| └───────────────────────────┘       |
|                                     |
| [Dismiss Alert]   [Log Details 📜 ] |
|                                     |
───────────────────────────────────────
```

---

### 📜 Event Log Screen

```plaintext
───────────────────────────────────────
| 📜 Recon Detection Log              |
───────────────────────────────────────
| Time       | Frequency  | RSSI      |
|------------|------------|-----------|
| 08:23:11   | 2.437 GHz  | -39 dBm ⚠️|
| 08:23:06   | 2.437 GHz  | -41 dBm   |
| 08:23:01   | 2.437 GHz  | -40 dBm   |
| 08:22:56   | 2.437 GHz  | -43 dBm   |
|                                     |
| ┌───────────────────────────┐       |
| │ Signal Pattern Summary:   │       |
| │                           │       |
| │ Pulses every ~5 sec ✔️    │       |
| │ Consistent RSSI ✔️        │       |
| │ Potential DF activity ⚠️  │       |
| └───────────────────────────┘       |
|                                     |
| [ Export Log ]      [ Clear Log 🗑️ ]|
|                                     |
───────────────────────────────────────
```

---

### ⚙️ Settings Screen

```plaintext
───────────────────────────────────────
| ⚙️ Settings                         |
───────────────────────────────────────
|                                     |
| Frequency Presets:                  |
| [x] 433 MHz      [ ] 868 MHz        |
| [x] 2.4 GHz      [ ] 5.8 GHz        |
|                                     |
| Custom Range:                       |
| Start: [ 2400 MHz ]                 |
| End:   [ 2485 MHz ]                 |
|                                     |
| Detection Sensitivity:              |
| Low ◄─|───────●───────|─► High      |
|                                     |
| Alert Settings:                     |
| [x] Audio Alert 🔊                  |
| [x] Visual Alert 📢                 |
|                                     |
| [ Save ]          [ Cancel ]        |
|                                     |
───────────────────────────────────────
```

---

## 🛡️ PANIC Mode Functions

When RF pings breach a defined proximity threshold (indicating immediate threat):

- **BlackBox Recording** (live audio, no immediate broadcast)
- **Intercept Active Communications**
- **Replay intercepted comms back on the same frequency and via speaker**

**Workflow:**

```
[RF Ping Arrives at Base]
            │
            ▼
[Activate PANIC Mode]
    ├───► [Start BlackBox Mic Recording 🔴]
    │
    └───► [Scan for Active Comms 📡]
                │
                ▼
        [Intercept Active Comms 🎧]
                │
                ▼
[Replay Intercepted Audio (Echo & Speaker 🔊)]
```

---

## 🖥️ Installation and Usage

Mayhem SDK Firmware Build

---

## ⚠️ Disclaimer

Ensure compliance with local RF regulations. This software is intended for legal, ethical use only.

---

## 📝 License

N/a
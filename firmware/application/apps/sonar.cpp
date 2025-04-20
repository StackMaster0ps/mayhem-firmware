#include <hackrf.h>
#include <cstdio>
#include <cmath>
#include <vector>

// Global Definitions
hackrf_device* device = nullptr;
bool panic_mode_active = false;
float at_base_rssi_threshold = -25.0f;  // Calibrate as needed
uint64_t intercept_freq = 2400000000ULL; // Example: 2.4 GHz
std::vector<int16_t> audio_buffer; // Demodulated audio storage

// DSP constants
const int SAMPLE_RATE = 10e6;
const int BUFFER_LENGTH = 262144; // HackRF default

// Initialize HackRF
bool init_hackrf() {
    if (hackrf_init() != HACKRF_SUCCESS) return false;
    if (hackrf_open(&device) != HACKRF_SUCCESS) return false;
    hackrf_set_freq(device, intercept_freq);
    hackrf_set_sample_rate(device, SAMPLE_RATE);
    hackrf_set_lna_gain(device, 32);
    hackrf_set_vga_gain(device, 40);
    return true;
}

// Cleanup HackRF
void close_hackrf() {
    hackrf_stop_rx(device);
    hackrf_stop_tx(device);
    hackrf_close(device);
    hackrf_exit();
}

// Simple RSSI estimation from IQ samples
float estimate_rssi(int8_t* buf, int length) {
    double total_power = 0.0;
    for (int i = 0; i < length; i += 2) {
        double I = buf[i] / 128.0;
        double Q = buf[i+1] / 128.0;
        total_power += (I * I + Q * Q);
    }
    double mean_power = total_power / (length / 2);
    return 10 * log10(mean_power);
}

// Simple FM Demodulation (for illustration)
void fm_demodulate(int8_t* buf, int length, std::vector<int16_t>& audio_out) {
    static float prev_phase = 0;
    for (int i = 0; i < length; i += 2) {
        float I = buf[i] / 128.0;
        float Q = buf[i+1] / 128.0;
        float phase = atan2f(Q, I);
        float delta = phase - prev_phase;
        prev_phase = phase;
        int16_t audio_sample = (int16_t)(delta * 10000); // scale factor
        audio_out.push_back(audio_sample);
    }
}

// RX Callback
int rx_callback(hackrf_transfer* transfer) {
    float rssi = estimate_rssi((int8_t*)transfer->buffer, transfer->valid_length);
    
    if (!panic_mode_active && rssi > at_base_rssi_threshold) {
        panic_mode_active = true;
        printf("[PANIC MODE ACTIVATED] RSSI: %.2f dB\n", rssi);
    }
    
    if (panic_mode_active) {
        audio_buffer.clear();
        fm_demodulate((int8_t*)transfer->buffer, transfer->valid_length, audio_buffer);
        // BlackBox storage (pseudo)
        printf("[BlackBox] Audio samples recorded: %zu\n", audio_buffer.size());
        // Proceed to TX echo/replay (once audio_buffer is filled)
        hackrf_stop_rx(device);
        hackrf_start_tx(device, tx_callback, nullptr);
    }
    
    return 0;
}

// TX Callback (Echo/Replay intercepted audio)
int tx_callback(hackrf_transfer* transfer) {
    static size_t audio_pos = 0;
    for (size_t i = 0; i < transfer->buffer_length && audio_pos < audio_buffer.size(); i += 2) {
        int16_t sample = audio_buffer[audio_pos++];
        transfer->buffer[i] = (sample >> 8) & 0xFF;
        transfer->buffer[i + 1] = sample & 0xFF;
    }

    if (audio_pos >= audio_buffer.size()) {
        printf("[Echo Replay Completed]\n");
        hackrf_stop_tx(device);
        panic_mode_active = false;
        audio_pos = 0;
        hackrf_start_rx(device, rx_callback, nullptr);
    }

    return 0;
}

int main() {
    if (!init_hackrf()) {
        fprintf(stderr, "HackRF initialization failed.\n");
        return -1;
    }

    hackrf_start_rx(device, rx_callback, nullptr);

    // Main event loop (simplified for demo)
    printf("Scanning RF signals... Press ENTER to stop.\n");
    getchar();

    close_hackrf();
    return 0;
}

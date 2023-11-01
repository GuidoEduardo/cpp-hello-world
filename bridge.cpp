#include <iostream>

class Device {
    private:
        bool mEnabled;
        float mVolume;
        int mChannel;

    public:
        virtual void Enable() {
            mEnabled = true;
        }

        virtual void Disable() {
            mEnabled = false;
        }

        virtual bool IsEnabled() const {
            return mEnabled;
        }

        virtual void SetVolume(float percent) {
            mVolume = percent;
        }

        virtual float GetVolume() const {
            return mVolume;
        }
        virtual void SetChannel(int channel) {
            mChannel = channel;
        }

        virtual int GetChannel() const {
            return mChannel;
        }
};

class TV : public Device {};
class Radio : public Device {};

class Remote {
    private:
        Device* mDevice;

    public:
        Remote(Device* device)
            : mDevice(device) {}
        
        void TogglePower() {
            if (mDevice->IsEnabled()) {
                mDevice->Disable();
            } else {
                mDevice->Enable();
            }
        }

        void VolumeUp() {
            mDevice->SetVolume(100);
        }

        void VolumeDown() {
            mDevice->SetVolume(50);
        }

        void ChannelUp() {
            mDevice->SetChannel(20);
        }

        void ChannelDown() {
            mDevice->SetChannel(10);
        }
};

int main() {
    std::cout << "Starting Bridge pattern." << std::endl;

    TV tv;
    Radio radio;

    Remote tvRemote(&tv);
    tvRemote.VolumeUp();
    std::cout << "TV volume is " << tv.GetVolume() << "%" << std::endl << std::endl;

    Remote radioRemote(&radio);
    radioRemote.TogglePower();
    std::string power = (radio.IsEnabled()) ? "On" : "Off";
    std::cout << "Radio is " << power << std::endl;

    return 0;
}
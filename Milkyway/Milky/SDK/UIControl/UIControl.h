#pragma once

class UIControl {
public:
	BUILD_ACCESS(std::string, layerName, 0x18);
	BUILD_ACCESS(float, scale, 0x40);
	BUILD_ACCESS(float, posX, 0x78);
	BUILD_ACCESS(float, posY, 0x7C);
	BUILD_ACCESS(float, maxSizeX, 0x80);
	BUILD_ACCESS(float, maxSizeY, 0x84);
	BUILD_ACCESS(std::vector<std::shared_ptr<UIControl>>, children, 0xA0);

    //from flarial
    void getAllControls(std::vector<std::shared_ptr<UIControl>>& list) {
        for (auto& control : this->children) {
            list.emplace_back(control);
            control->getAllControls(list);
        }
    }

    void forEachControl(std::function<void(std::shared_ptr<UIControl>&)>&& func) {

        std::vector<std::shared_ptr<UIControl>> writeList;
        this->getAllControls(writeList);

        for (auto& control : writeList) {
            func(control);
        }
    }
};
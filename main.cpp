#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Simplin");
    ImGui::SFML::Init(window);

    int font_size = 22;
    
    bool flashcards_window = false;

    bool maths_window = false;
    bool geography_window = false;
    bool english_window = false;
    bool history_window = false;
    bool spanish_window = false;
    bool computing_window = false;
    bool biology_window = false;
    bool physics_window = false;
    bool chemistry_window = false;

    while (window.isOpen()) {

        ImGui::GetIO().FontGlobalScale = float(font_size) / 10;

        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.f / 1000000.f));

        ImGui::SetNextWindowSize(ImVec2(1000, 800));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("RevisionOS");
        {
            ImGui::SetCursorPos(ImVec2(25, 50));
            if (ImGui::Button("Flashcards", ImVec2(950, 400)))
            {
                flashcards_window = true;
            }
            
            ImGui::SetCursorPos(ImVec2(20, 500));
            if (ImGui::Button("Maths", ImVec2(150, 100)))
            {
                maths_window = true;
            }

            ImGui::SetCursorPos(ImVec2(180, 500));
            if (ImGui::Button("English", ImVec2(150, 100)))
            {
                english_window = true;
            }

            ImGui::SetCursorPos(ImVec2(340, 500));
            if (ImGui::Button("Biology", ImVec2(150, 100)))
            {
                biology_window = true;
            }

            ImGui::SetCursorPos(ImVec2(500, 500));
            if (ImGui::Button("Physics", ImVec2(150, 100)))
            {
                physics_window = true;
            }

            ImGui::SetCursorPos(ImVec2(660, 500));
            if (ImGui::Button("Chemistry", ImVec2(150, 100)))
            {
                chemistry_window = true;
            }

            ImGui::SetCursorPos(ImVec2(820, 500));
            if (ImGui::Button("Computing", ImVec2(150, 100)))
            {
                computing_window = true;
            }

            ImGui::SetCursorPos(ImVec2(20, 650));
            if (ImGui::Button("Geography", ImVec2(150, 100)))
            {
                geography_window = true;
            }

            ImGui::SetCursorPos(ImVec2(180, 650));
            if (ImGui::Button("History", ImVec2(150, 100)))
            {
                history_window = true;
            }

            ImGui::SetCursorPos(ImVec2(340, 650));
            if (ImGui::Button("Spanish", ImVec2(150, 100)))
            {
                spanish_window = true;
            }

            ImGui::End();
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <fstream>
#include <random>

using namespace std::chrono_literals;

auto get_question(std::string& s) -> std::string
{
    auto index = s.find("||");
    return s.substr(0, index - 1);
}

auto get_answer(std::string& s) -> std::string
{
    auto index = s.find("||");
    return s.substr(index + 3, s.size());
}

auto get_from_file_into_vector(std::vector<std::pair<std::string, std::string>>& v, std::string filename) -> void
{
    std::string line{};
    std::ifstream myfile(filename.c_str());
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            std::string first_part = get_question(line);
            std::string second_part = get_answer(line);
            v.emplace_back(std::pair{ first_part, second_part });
        }
        myfile.close();
    }
}

auto get_random_number(int end) -> int
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, end);

    return dist6(rng);
}

int main() {
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    sf::RenderWindow window(sf::VideoMode(1000, 800), "RevisionOS");
    ImGui::SFML::Init(window);

    int font_size = 22;
    
    bool flashcards_window = false;
    bool flashcards = false;

    bool maths_window = false;
    bool geography_window = false;
    bool english_window = false;
    bool history_window = false;
    bool spanish_window = false;
    bool computing_window = false;
    bool biology_window = false;
    bool physics_window = false;
    bool chemistry_window = false;
    bool geog_fieldwork = false;
    bool maths_questions = false;

    bool hstry_structure_q = false;
    bool interact_math_questions = false;

    bool is_flashcard_question = true;
    bool is_flashcard_answer = false;
    int current_flashcard_index = 0;
    bool close_flashcard = false;

    std::vector<std::pair<std::string, std::string>> v{};

    std::pair<std::string, std::string> current_flashcard{};

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

        if (flashcards_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::Begin("Flashcards");

            static bool selection[10] = { true, false, false, false, false, false, false, false, false };
            ImGui::Selectable("Maths", &selection[0]);
            ImGui::Selectable("English", &selection[1]);
            ImGui::Selectable("Biology", &selection[2]);
            ImGui::Selectable("Chemistry", &selection[3]);
            ImGui::Selectable("Physics", &selection[4]);
            ImGui::Selectable("Computing", &selection[5]);
            ImGui::Selectable("Spanish", &selection[6]);
            ImGui::Selectable("Geography", &selection[7]);
            ImGui::Selectable("History", &selection[8]);

            ImGui::NewLine();

            if (ImGui::Button("Generate", ImVec2(50, 50)))
            {
                if (selection[0])
                {
                    get_from_file_into_vector(v, "maths.txt");
                }
                if (selection[1])
                {
                    get_from_file_into_vector(v, "english.txt");
                }
                if (selection[2])
                {
                    get_from_file_into_vector(v, "biology.txt");
                }
                if (selection[3])
                {
                    get_from_file_into_vector(v, "chemistry.txt");
                }
                if (selection[4])
                {
                    get_from_file_into_vector(v, "physics.txt");
                }
                if (selection[5])
                {
                    get_from_file_into_vector(v, "computing.txt");
                }
                if (selection[6])
                {
                    get_from_file_into_vector(v, "spanish.txt");
                }
                if (selection[7])
                {
                    get_from_file_into_vector(v, "geography.txt");
                }
                if (selection[8])
                {
                    get_from_file_into_vector(v, "history.txt");
                }
                flashcards = true;
            }

            ImGui::End();
        }

        if (flashcards)
        {
            ImGui::SetNextWindowPos(ImVec2(400, 200));
            ImGui::Begin("Flashcard");

            //while (!close_flashcard)
            //{
                current_flashcard_index = get_random_number(v.size() - 1);
                current_flashcard = v[current_flashcard_index];
                if (is_flashcard_question)
                {
                    ImGui::Text(current_flashcard.first.c_str());
                }
                else if (is_flashcard_answer)
                {
                    ImGui::Text(current_flashcard.second.c_str());
                }

                if (ImGui::ArrowButton("##left", ImGuiDir_Left))
                {
                    if (current_flashcard_index > 0)
                    {
                        current_flashcard = v[current_flashcard_index - 1];
                        current_flashcard_index--;
                    }
                }
                ImGui::SameLine();
                if (ImGui::ArrowButton("##right", ImGuiDir_Right))
                {
                    if (current_flashcard_index < (v.size() - 1))
                    {
                        current_flashcard = v[current_flashcard_index + 1];
                        current_flashcard_index++;
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Random"))
                {
                    current_flashcard_index = get_random_number(v.size() - 1);
                    current_flashcard = v[current_flashcard_index];
                }
                ImGui::NewLine();
                if (ImGui::Button("Quit"))
                {
                    close_flashcard = true;
                }
            //}

            ImGui::End();
        }

        if (geography_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Geography");

            if (ImGui::Button("Fieldwork"))
            {
                geog_fieldwork = true;
            }

            ImGui::End();
        }

        if (geog_fieldwork)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Geography Fieldwork");

            ImGui::TextWrapped("Ashbrook");

            ImGui::End();
        }

        if (history_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("History");

            if (ImGui::Button("How to strucuture questions?"))
            {
                hstry_structure_q = true;
            }

            ImGui::End();
        }

        if (hstry_structure_q)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("History Question Structure");
            ImGui::TextWrapped("6 Marker:\n\n First sentence must answer the question --> \"The author gives the impression that ... was ...\""
                               "\nThen back it up by picking 2 or 3 qutoes --> \"This is evident when it states\""
                               "\nOne sentance on the tone used by the author and how it shows their view --> \"The ... tone is shown by the use of words such as...\""
                               "\nComment on what the author has failed to acknowledge or fully appreciate --> \"However, the author has failed to acknowledge ... that ...\""
                               "\n\n\n8 Marker: \n\n Question is looking for 2 effects so --> \"one effect of ... \" and \"another effect of ... \""
                               "\n\n\n16 Marker: \n\n Para 1: overview of arguements in A, B and C. Then say however this evidence in A, B and C to suggest otherwise"
                               "\nPara 2: Do the arguement in the question using quotes from extract C and A and B. Then own knowledge"
                               "\nPara 3: Find different arguement, evidence from A, B, C"
                               "Conclusion say although arguement from 2 or 3 main reason, 2 or 3 say why it is the right argument and why disagree"
                               );
            ImGui::End();
        }

        if (spanish_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Spanish");

            ImGui::End();
        }

        if (computing_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Computing");

            ImGui::End();
        }

        if (english_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("English");

            ImGui::End();
        }

        if (maths_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Maths");

            maths_questions = true;

            ImGui::End();
        }

        if (maths_questions)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("English");

            ImGui::TextWrapped("factorize x^2 + x - 6");
            ImGui::TextWrapped("What is the quadratic forumula?");
            ImGui::TextWrapped("What is (x^2)^3");
            
            if (ImGui::Button("Interact Questions"))
            {
                interact_math_questions = true;
            }

            ImGui::End();
        }

        if (interact_math_questions)
        {
            int x1 = get_random_number(10) - 5;
            int y1 = get_random_number(10) - 5;
            int x2 = get_random_number(10) - 5;
            int y2 = get_random_number(10) - 5;

            std::string first_coord = "(" + std::to_string(x1) + ", " + std::to_string(y1) + ")";
            std::string second_coord = "(" + std::to_string(x2) + ", " + std::to_string(y2) + ")";

            std::string question_coords = "What is the equation of the line that passes through points: " + first_coord + " and " + second_coord;

            ImGui::TextWrapped(question_coords.c_str());
        }

        if (biology_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Biology");

            ImGui::TextWrapped("What are the organelles in a plant cell?");

            ImGui::End();
        }

        if (physics_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Physics");

            ImGui::TextWrapped("E = QV");
            ImGui::TextWrapped("f = ma");
            ImGui::TextWrapped("V = f lambda");
            ImGui::TextWrapped("w = f/d");
            ImGui::TextWrapped("Q = IT");

            ImGui::End();
        }

        if (chemistry_window)
        {
            ImGui::SetNextWindowSize(ImVec2(1000, 800));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::Begin("Chemistry");

            ImGui::TextWrapped("mole = (mass in grams) / (relative molecular mass)");

            ImGui::End();
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return 0;
}
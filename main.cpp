// ============================================================
//  Простой графический калькулятор на Dear ImGui + GLFW
//  Структура проекта: CMakeLists.txt + main.cpp
//  Библиотеки скачиваются автоматически через FetchContent.
// ============================================================

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <cmath>
#include <cstdio>

// Фиксированный размер окна приложения (пользователь не может его менять)
static const int WINDOW_WIDTH  = 480;
static const int WINDOW_HEIGHT = 260;

int main()
{
    // ---------- Инициализация GLFW ----------
    if (!glfwInit())
        return 1;

    // OpenGL 3.3 Core — профиль, поддерживаемый бэкендом imgui_impl_opengl3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Окно фиксированного размера: без флага GLFW_RESIZABLE оно не ресайзится
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                          "Калькулятор ImGui", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // вертикальная синхронизация

    // ---------- Инициализация Dear ImGui ----------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // управление с клавиатуры
    ImGui::StyleColorsDark();

    // Дополнительный крупный шрифт для вывода результата.
    ImFontConfig cfg;
    cfg.SizePixels = 32.0f;                  // размер крупного шрифта в пикселях
    ImFont* bigFont = io.Fonts->AddFontDefault(&cfg);
    if (!bigFont) bigFont = io.Fonts->Fonts[0]; // страховка: используем стандартный

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // ---------- Состояние калькулятора ----------
    float a = 0.0f;          // "Число А"
    float b = 0.0f;          // "Число Б"
    float result = 0.0f;     // результат последней операции
    bool  hasResult = false; // была ли выполнена хотя бы одна операция
    bool  divByZero = false; // флаг ошибки "деление на ноль"

    char resultBuf[64] = ""; // строковое представление результата

    // ---------- Главный цикл ----------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Единственное окно приложения — на всю клиентскую область,
        // без заголовка, рамок и возможности изменения размера.
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT));
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove    | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus;
        ImGui::Begin("Calculator", nullptr, window_flags);

        // --- Два числовых поля ввода ---
        ImGui::InputFloat("Число А", &a, 0.0f, 0.0f, "%.3f");
        ImGui::InputFloat("Число Б", &b, 0.0f, 0.0f, "%.3f");

        ImGui::Spacing();

        // --- Четыре кнопки в ряд ---
        auto calcResult = [&](char op)
        {
            divByZero = false;
            switch (op)
            {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (std::fabs(b) < 1e-9f)
                        divByZero = true;   // проверка на деление на ноль
                    else
                        result = a / b;
                    break;
            }
            hasResult = true;
        };

        if (ImGui::Button("+", ImVec2(90, 40))) calcResult('+');
        ImGui::SameLine();
        if (ImGui::Button("-", ImVec2(90, 40))) calcResult('-');
        ImGui::SameLine();
        if (ImGui::Button("*", ImVec2(90, 40))) calcResult('*');
        ImGui::SameLine();
        if (ImGui::Button("/", ImVec2(90, 40))) calcResult('/');

        // --- Вывод результата ---
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (divByZero)
        {
            // Ошибка — крупным красным текстом
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.25f, 0.25f, 1.0f));
            ImGui::PushFont(bigFont);
            ImGui::TextUnformatted("Ошибка: деление на ноль!");
            ImGui::PopFont();
            ImGui::PopStyleColor();
        }
        else if (hasResult)
        {
            std::snprintf(resultBuf, sizeof(resultBuf), "%g", (double)result);
            ImGui::PushFont(bigFont);
            ImGui::Text("Результат: %s", resultBuf);
            ImGui::PopFont();
        }
        else
        {
            ImGui::TextDisabled("Введите числа и выберите операцию");
        }

        ImGui::End();

        // ---------- Отрисовка ----------
        ImGui::Render();
        int displayW, displayH;
        glfwGetFramebufferSize(window, &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // ---------- Завершение ----------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

#include "Screen.hpp"
#include "Player.hpp"
#include "StopWatch.hpp"
#include "Map.hpp"
#include <algorithm>
#include <Windows.h>

bool AsyncKeyIsPressed(wchar_t const ch) noexcept
{
    return GetAsyncKeyState((unsigned short)ch) & 0x8000;
}

int main()
{
    Screen screen;
    Player player;

    HANDLE hConsole =
        CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    SetConsoleActiveScreenBuffer(hConsole);

    StopWatch stopWatch;

    bool redraw = true;

    // Game Loop
    while (true)
    {
        // Q means stop
        if (AsyncKeyIsPressed('Q')) break;

        float const fElapsedTime = stopWatch.Ellapsed().count();

        // Controls
        // Handle CCW Rotation
        if (AsyncKeyIsPressed('A'))
        {
            player.TurnCounterClockWise(fElapsedTime);
            redraw = true;
        }
        else if (AsyncKeyIsPressed('D'))
        {
            player.TurnClockWise(fElapsedTime);
            redraw = true;
        }

        if (AsyncKeyIsPressed('W'))
        {
            player.WalkForward(fElapsedTime);

            if (Map::GetPix((int)player.X(), (int)player.Y()) == '#')
            {
                player.WalkBackward(fElapsedTime);
            }
            else
            {
                redraw = true;
            }
        }
        else if (AsyncKeyIsPressed('S'))
        {
            player.WalkBackward(fElapsedTime);

            if (Map::GetPix((int)player.X(), (int)player.Y()) == '#')
            {
                player.WalkForward(fElapsedTime);
            }
            else
            {
                redraw = true;
            }
        }

        if (!redraw) continue;

        for (int x = 0; x < screen.Width(); ++x)
        {
            float const fRayAngle =
                (player.Angle() - player.FieldOfView() / 2.f) + ((float)x / screen.Width()) * player.FieldOfView();
            float const fEyeX = std::sinf(fRayAngle);
            float const fEyeY = std::cosf(fRayAngle);

            float fDistanceToWall = 0.f;

            bool bHitWall = false;
            bool bBoundary = false;

            while (!bHitWall && fDistanceToWall < Map::Depth())
            {
                int const nTestX = (int)(player.X() + fEyeX * fDistanceToWall);
                int const nTestY = (int)(player.Y() + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= Map::Width() || nTestY < 0 || nTestY >= Map::Height())
                {
                    bHitWall = true;
                    fDistanceToWall = Map::Depth();
                }
                else if (Map::GetPix(nTestX, nTestY) == '#')
                {
                    bHitWall = true;
                    std::pair<float, float> p[4];
                    int i = 0;

                    for (int tx = 0; tx < 2; ++tx)
                        for (int ty = 0; ty < 2; ++ty)
                        {
                            float const vy = (float)nTestY + ty - player.Y();
                            float const vx = (float)nTestX + tx - player.X();
                            float const d = std::sqrtf(vx * vx + vy * vy);
                            float const dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                            p[i++] = std::pair(d, dot);
                        }

                    std::sort(std::begin(p), std::end(p), [](auto const& left, auto const& right)
                        {
                            return left.first < right.first;
                        });

                    float const fBound = 0.005f;
                    if (std::acos(p[0].second) < fBound
                        || std::acos(p[1].second) < fBound)
                        bBoundary = true;
                }

                fDistanceToWall += 0.1f;
            }

            int const nCeiling = int(screen.Height() / 2.f - screen.Height() / fDistanceToWall);
            int const nFloor = screen.Height() - nCeiling;


            // Set shades
            for (int y = 0; y < screen.Height(); ++y)
            {
                if (y < nCeiling)
                    screen.SetPix(x, y, ' ');
                else if (y > nCeiling && y <= nFloor)
                {
                    wchar_t nShade;

                    if (bBoundary) nShade = 0x0020;
                    else if (fDistanceToWall <= Map::Depth() / 4.f) nShade = 0x2588; // Very close
                    else if (fDistanceToWall <= Map::Depth() / 3.f) nShade = 0x2593;
                    else if (fDistanceToWall <= Map::Depth() / 2.f) nShade = 0x2592;
                    else if (fDistanceToWall <= Map::Depth()) nShade = 0x2591;
                    else nShade = 0x0020; // Too far away
                    screen.SetPix(x, y, nShade);
                }
                else
                {
                    wchar_t nShade;
                    float const b = 1.f - (((float)y - screen.Height() / 2.f) / ((float)screen.Height() / 2.f));
                    if (b < 0.25f) nShade = L'#';
                    else if (b < 0.5) nShade = L'x';
                    else if (b < 0.75) nShade = L'.';
                    else if (b < 0.9) nShade = L'-';
                    else nShade = L' ';
                    screen.SetPix(x, y, nShade);
                }

            }
        }

        for (int nx = 0; nx < Map::Width(); ++nx)
            for (int ny = 0; ny < Map::Height(); ++ny)
                screen.SetPix(nx, ny + 1, Map::GetPix(nx, ny));

        screen.SetPix((int)player.X(), (int)player.Y() + 1, 'P');

        DWORD dwBytesWritten;
        WriteConsoleOutputCharacterW(hConsole,
            screen.Buffer(),
            screen.Height() * screen.Width(),
            { 0, 0 },
            &dwBytesWritten);
        redraw = false;
    }

    CloseHandle(hConsole);
}
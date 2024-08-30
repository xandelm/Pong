// Código base (inicial) para implementação do TP3 de CG
#include <GL/glut.h>

// Tamanho da janela
const int width = 800;
const int height = 600;

// Posições e dimensões das barras
float barWidth = 20.0f;
float barHeight = 100.0f;
float bar1Y = height / 2 - barHeight / 2;
float bar2Y = height / 2 - barHeight / 2;

// Posição e velocidade da bola
float ballX = width / 2;
float ballY = height / 2;
float ballSize = 20.0f;

// Velocidades
float barSpeed = 10.0f;
float ballXSpeed = 5.0f;
float ballYSpeed = 5.0f;

// Placar
int score1 = 0;
int score2 = 0;

int barHorizontalPadding = 25;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw bar1
    glRectf(10, bar1Y, 10 + barWidth, bar1Y + barHeight);

    // Draw bar2
    glRectf(width - 10 - barWidth, bar2Y, width - 10, bar2Y + barHeight);

    // Draw ball
    glRectf(ballX - ballSize / 2, ballY - ballSize / 2, ballX + ballSize / 2, ballY + ballSize / 2);

    // Draw score
    glRasterPos2f(width / 2 - 50, height - 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + score1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + score2);

    glBegin(GL_QUADS);

    glVertex2f(-0.5f, -0.5f); // x, y
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    // Espaço para desenhar as barras e a bola

    glutSwapBuffers();
}

void update(int value)
{

    // lógica de movimentação e colisão da bola
    ballX += ballXSpeed;
    ballY += ballYSpeed;

    // colisão com chão e teto
    if (ballY + ballSize / 2 > height || ballY - ballSize / 2 < 0)
    {
        ballYSpeed = -ballYSpeed;
    }

    // colisão com barras
    if (
        (ballX - ballSize / 2 < barWidth + 10 && ballY > bar1Y && ballY < bar1Y + barHeight) ||      // colisão barra esquerda
        (ballX + ballSize / 2 > width - barWidth - 10 && ballY > bar2Y && ballY < bar2Y + barHeight) // colisão barra direita
    )
    {
        ballXSpeed = -ballXSpeed;
    }

    // colisão com paredes esquerda e direita
    if (ballX + ballSize / 2 > width || ballX - ballSize / 2 < 0)
    {
        if (ballX + ballSize / 2 > width)
            score1++;
        if (ballX - ballSize / 2 < 0)
            score2++;

        // reseta posição da bola
        ballX = width / 2;
        ballY = height / 2;
        ballXSpeed = 5.0f;
        ballYSpeed = 5.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void handleKeys(unsigned char key, int x, int y)
{
    // Espaço para configurar o estado das teclas ao pressionar
    switch (key)
    {
    case 'w':
        if (bar1Y + barHeight < height)
            bar1Y += barSpeed;
        break;
    case 's':
        if (bar1Y > 0)
            bar1Y -= barSpeed;
        break;
    case '8':
        if (bar2Y + barHeight < height)
            bar2Y += barSpeed;
        break;
    case '2':
        if (bar2Y > 0)
            bar2Y -= barSpeed;
    default:
        break;
    }
}

// Função para evitar o redimensionamento da janela
void reshape(int w, int h)
{
    glutReshapeWindow(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // aqui a origem do sistema de coordenadas é colocada na parte inferior à esquerda
    gluOrtho2D(0.0, width, 0.0, height);
    glutPostRedisplay();
}

void Init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("TP3 - Jogo Pong");
}

int main(int argc, char **argv)
{
    Init(argc, argv);
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutKeyboardFunc(handleKeys);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
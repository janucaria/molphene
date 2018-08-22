#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <sstream>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <molphene/Scene.hpp>

const char* pdbhem = R"(
ATOM      1  CHA HEM A   1      -2.161  -0.125   0.490  1.00 10.00           C
ATOM      2  CHB HEM A   1       1.458  -3.419   0.306  1.00 10.00           C
ATOM      3  CHC HEM A   1       4.701   0.169  -0.069  1.00 10.00           C
ATOM      4  CHD HEM A   1       1.075   3.460   0.018  1.00 10.00           C
ATOM      5  C1A HEM A   1      -1.436  -1.305   0.380  1.00 10.00           C
ATOM      6  C2A HEM A   1      -2.015  -2.587   0.320  1.00 10.00           C
ATOM      7  C3A HEM A   1      -1.009  -3.500   0.270  1.00 10.00           C
ATOM      8  C4A HEM A   1       0.216  -2.803   0.298  1.00 10.00           C
ATOM      9  CMA HEM A   1      -1.175  -4.996   0.197  1.00 10.00           C
ATOM     10  CAA HEM A   1      -3.490  -2.893   0.314  1.00 10.00           C
ATOM     11  CBA HEM A   1      -3.998  -2.926  -1.129  1.00 10.00           C
ATOM     12  CGA HEM A   1      -5.473  -3.232  -1.136  1.00 10.00           C
ATOM     13  O1A HEM A   1      -6.059  -3.405  -0.094  1.00 10.00           O
ATOM     14  O2A HEM A   1      -6.137  -3.311  -2.300  1.00 10.00           O
ATOM     15  C1B HEM A   1       2.664  -2.707   0.308  1.00 10.00           C
ATOM     16  C2B HEM A   1       3.937  -3.328   0.418  1.00 10.00           C
ATOM     17  C3B HEM A   1       4.874  -2.341   0.314  1.00 10.00           C
ATOM     18  C4B HEM A   1       4.117  -1.079   0.139  1.00 10.00           C
ATOM     19  CMB HEM A   1       4.203  -4.798   0.613  1.00 10.00           C
ATOM     20  CAB HEM A   1       6.339  -2.497   0.365  1.00 10.00           C
ATOM     21  CBB HEM A   1       6.935  -3.419  -0.385  1.00 10.00           C
ATOM     22  C1C HEM A   1       3.964   1.345  -0.174  1.00 10.00           C
ATOM     23  C2C HEM A   1       4.531   2.601  -0.445  1.00 10.00           C
ATOM     24  C3C HEM A   1       3.510   3.536  -0.437  1.00 10.00           C
ATOM     25  C4C HEM A   1       2.304   2.846  -0.139  1.00 10.00           C
ATOM     26  CMC HEM A   1       5.991   2.880  -0.697  1.00 10.00           C
ATOM     27  CAC HEM A   1       3.649   4.981  -0.692  1.00 10.00           C
ATOM     28  CBC HEM A   1       4.201   5.407  -1.823  1.00 10.00           C
ATOM     29  C1D HEM A   1      -0.102   2.753   0.298  1.00 10.00           C
ATOM     30  C2D HEM A   1      -1.382   3.388   0.641  1.00 10.00           C
ATOM     31  C3D HEM A   1      -2.283   2.389   0.774  1.00 10.00           C
ATOM     32  C4D HEM A   1      -1.561   1.137   0.511  1.00 10.00           C
ATOM     33  CMD HEM A   1      -1.639   4.863   0.811  1.00 10.00           C
ATOM     34  CAD HEM A   1      -3.741   2.532   1.123  1.00 10.00           C
ATOM     35  CBD HEM A   1      -4.573   2.563  -0.160  1.00 10.00           C
ATOM     36  CGD HEM A   1      -6.032   2.706   0.189  1.00 10.00           C
ATOM     37  O1D HEM A   1      -6.372   2.776   1.347  1.00 10.00           O
ATOM     38  O2D HEM A   1      -6.954   2.755  -0.785  1.00 10.00           O
ATOM     39  NA  HEM A   1      -0.068  -1.456   0.321  1.00 10.00           N
ATOM     40  NB  HEM A   1       2.820  -1.386   0.207  1.00 10.00           N
ATOM     41  NC  HEM A   1       2.604   1.506  -0.033  1.00 10.00           N
ATOM     42  ND  HEM A   1      -0.276   1.431   0.298  1.00 10.00           N
ATOM     43 FE   HEM A   1       1.010   0.157  -0.060  1.00 10.00          FE
ATOM     44  HHB HEM A   1       1.498  -4.508   0.309  1.00 10.00           H
ATOM     45  HHC HEM A   1       5.786   0.229  -0.153  1.00 10.00           H
ATOM     46  HHD HEM A   1       1.018   4.543  -0.083  1.00 10.00           H
ATOM     47  HMA HEM A   1      -1.220  -5.306  -0.847  1.00 10.00           H
ATOM     48 HMAA HEM A   1      -0.328  -5.480   0.683  1.00 10.00           H
ATOM     49 HMAB HEM A   1      -2.097  -5.285   0.702  1.00 10.00           H
ATOM     50  HAA HEM A   1      -3.662  -3.862   0.782  1.00 10.00           H
ATOM     51 HAAA HEM A   1      -4.024  -2.121   0.869  1.00 10.00           H
ATOM     52  HBA HEM A   1      -3.825  -1.956  -1.597  1.00 10.00           H
ATOM     53 HBAA HEM A   1      -3.464  -3.697  -1.684  1.00 10.00           H
ATOM     54  HMB HEM A   1       3.256  -5.336   0.660  1.00 10.00           H
ATOM     55 HMBA HEM A   1       4.794  -5.175  -0.222  1.00 10.00           H
ATOM     56 HMBB HEM A   1       4.752  -4.948   1.543  1.00 10.00           H
ATOM     57  HAB HEM A   1       6.927  -1.863   1.011  1.00 10.00           H
ATOM     58  HBB HEM A   1       7.994  -3.600  -0.277  1.00 10.00           H
ATOM     59 HBBA HEM A   1       6.360  -3.987  -1.102  1.00 10.00           H
ATOM     60  HMC HEM A   1       6.554   1.949  -0.639  1.00 10.00           H
ATOM     61 HMCA HEM A   1       6.110   3.316  -1.689  1.00 10.00           H
ATOM     62 HMCB HEM A   1       6.362   3.578   0.053  1.00 10.00           H
ATOM     63  HAC HEM A   1       3.303   5.694   0.042  1.00 10.00           H
ATOM     64  HBC HEM A   1       4.614   4.696  -2.523  1.00 10.00           H
ATOM     65 HBCA HEM A   1       4.235   6.464  -2.043  1.00 10.00           H
ATOM     66  HMD HEM A   1      -0.715   5.415   0.639  1.00 10.00           H
ATOM     67 HMDA HEM A   1      -2.394   5.185   0.094  1.00 10.00           H
ATOM     68 HMDB HEM A   1      -1.994   5.055   1.824  1.00 10.00           H
ATOM     69  HAD HEM A   1      -4.052   1.687   1.738  1.00 10.00           H
ATOM     70 HADA HEM A   1      -3.893   3.459   1.677  1.00 10.00           H
ATOM     71  HBD HEM A   1      -4.262   3.408  -0.775  1.00 10.00           H
ATOM     72 HBDA HEM A   1      -4.421   1.636  -0.714  1.00 10.00           H
ATOM     73  H2A HEM A   1      -7.082  -3.510  -2.254  1.00 10.00           H
ATOM     74  H2D HEM A   1      -7.877   2.847  -0.512  1.00 10.00           H
ATOM     75  HHA HEM A   1      -3.246  -0.188   0.567  1.00 10.00           H
CONECT    1    5   32   75
CONECT    2    8   15   44
CONECT    3   18   22   45
CONECT    4   25   29   46
CONECT    5    1    6   39
CONECT    6    5    7   10
CONECT    7    6    8    9
CONECT    8    2    7   39
CONECT    9    7   47   48   49
CONECT   10    6   11   50   51
CONECT   11   10   12   52   53
CONECT   12   11   13   14
CONECT   13   12
CONECT   14   12   73
CONECT   15    2   16   40
CONECT   16   15   17   19
CONECT   17   16   18   20
CONECT   18    3   17   40
CONECT   19   16   54   55   56
CONECT   20   17   21   57
CONECT   21   20   58   59
CONECT   22    3   23   41
CONECT   23   22   24   26
CONECT   24   23   25   27
CONECT   25    4   24   41
CONECT   26   23   60   61   62
CONECT   27   24   28   63
CONECT   28   27   64   65
CONECT   29    4   30   42
CONECT   30   29   31   33
CONECT   31   30   32   34
CONECT   32    1   31   42
CONECT   33   30   66   67   68
CONECT   34   31   35   69   70
CONECT   35   34   36   71   72
CONECT   36   35   37   38
CONECT   37   36
CONECT   38   36   74
CONECT   39    5    8   43
CONECT   40   15   18   43
CONECT   41   22   25   43
CONECT   42   29   32   43
CONECT   43   39   40   41   42
CONECT   44    2
CONECT   45    3
CONECT   46    4
CONECT   47    9
CONECT   48    9
CONECT   49    9
CONECT   50   10
CONECT   51   10
CONECT   52   11
CONECT   53   11
CONECT   54   19
CONECT   55   19
CONECT   56   19
CONECT   57   20
CONECT   58   21
CONECT   59   21
CONECT   60   26
CONECT   61   26
CONECT   62   26
CONECT   63   27
CONECT   64   28
CONECT   65   28
CONECT   66   33
CONECT   67   33
CONECT   68   33
CONECT   69   34
CONECT   70   34
CONECT   71   35
CONECT   72   35
CONECT   73   14
CONECT   74   38
CONECT   75    1
END   
)";

const char* pdbmoi = R"(
HEADER    NONAME 05-Jun-11
TITLE     Produced by PDBeChem
COMPND    MOI      
AUTHOR    EBI-PDBe Generated
REVDAT   1  05-Jun-11     0
ATOM      1  C1  MOI     0      52.889  56.876   6.111  1.00 20.00           C+0
ATOM      2  C2  MOI     0      52.593  58.125   8.458  1.00 20.00           C+0
ATOM      3  C3  MOI     0      53.292  57.147   7.454  1.00 20.00           C+0
ATOM      4  C4  MOI     0      54.490  56.543   7.888  1.00 20.00           C+0
ATOM      5  C5  MOI     0      55.140  56.671   9.260  1.00 20.00           C+0
ATOM      6  C6  MOI     0      54.939  58.162   9.737  1.00 20.00           C+0
ATOM      7  C7  MOI     0      54.484  55.671  10.281  1.00 20.00           C+0
ATOM      8  C8  MOI     0      53.040  56.011  10.627  1.00 20.00           C+0
ATOM      9  C9  MOI     0      51.423  57.620  11.253  1.00 20.00           C+0
ATOM     10  C10 MOI     0      53.702  56.051   5.280  1.00 20.00           C+0
ATOM     11  C11 MOI     0      54.940  55.471   5.745  1.00 20.00           C+0
ATOM     12  C12 MOI     0      55.291  55.759   7.082  1.00 20.00           C+0
ATOM     13  C13 MOI     0      56.598  56.227   8.951  1.00 20.00           C+0
ATOM     14  C14 MOI     0      57.583  57.425   8.728  1.00 20.00           C+0
ATOM     15  C15 MOI     0      56.904  58.746   8.285  1.00 20.00           C+0
ATOM     16  C16 MOI     0      55.671  59.094   8.739  1.00 20.00           C+0
ATOM     17  C17 MOI     0      53.354  58.377   9.880  1.00 20.00           C+0
ATOM     18  N1  MOI     0      52.862  57.438  10.978  1.00 20.00           N+0
ATOM     19  O1  MOI     0      55.707  54.704   4.926  1.00 20.00           O+0
ATOM     20  O2  MOI     0      58.577  57.099   7.773  1.00 20.00           O+0
ATOM     21  O3  MOI     0      56.453  55.336   7.749  1.00 20.00           O+0
ATOM     22  H1  MOI     0      51.951  57.303   5.716  1.00 20.00           H+0
ATOM     23  H21 MOI     0      52.401  59.102   7.957  1.00 20.00           H+0
ATOM     24  H22 MOI     0      51.548  57.784   8.647  1.00 20.00           H+0
ATOM     25  H6  MOI     0      55.387  58.404  10.728  1.00 20.00           H+0
ATOM     26  H71 MOI     0      54.563  54.622   9.911  1.00 20.00           H+0
ATOM     27  H72 MOI     0      55.102  55.590  11.205  1.00 20.00           H+0
ATOM     28  H81 MOI     0      52.349  55.710   9.804  1.00 20.00           H+0
ATOM     29  H82 MOI     0      52.654  55.347  11.436  1.00 20.00           H+0
ATOM     30  H91 MOI     0      51.288  58.694  11.517  1.00 20.00           H+0
ATOM     31  H92 MOI     0      50.766  57.284  10.416  1.00 20.00           H+0
ATOM     32  H93 MOI     0      51.028  56.920  12.026  1.00 20.00           H+0
ATOM     33  H10 MOI     0      53.363  55.856   4.248  1.00 20.00           H+0
ATOM     34  H13 MOI     0      57.067  55.697   9.812  1.00 20.00           H+0
ATOM     35  H14 MOI     0      58.031  57.600   9.733  1.00 20.00           H+0
ATOM     36  H15 MOI     0      57.329  59.494   7.595  1.00 20.00           H+0
ATOM     37  H16 MOI     0      55.297  60.049   8.333  1.00 20.00           H+0
ATOM     38  H17 MOI     0      53.122  59.430  10.160  1.00 20.00           H+0
ATOM     39  HO1 MOI     0      56.521  54.322   5.231  1.00 20.00           H+0
ATOM     40  HO2 MOI     0      59.174  57.825   7.637  1.00 20.00           H+0
CONECT    1   10    3   22
CONECT    2   17    3   23   24
CONECT    3    1    2    4
CONECT    4   12    3    5
CONECT    5   13    4    6    7
CONECT    6   16   17    5   25
CONECT    7    5    8   26   27
CONECT    8    7   28   29   18
CONECT    9   30   31   32   18
CONECT   10    1   11   33
CONECT   11   10   12   19
CONECT   12   11    4   21
CONECT   13   14    5   34   21
CONECT   14   13   15   35   20
CONECT   15   14   16   36
CONECT   16   15    6   37
CONECT   17    2    6   38   18
CONECT   18   17    8    9
CONECT   19   11   39
CONECT   20   14   40
CONECT   21   12   13
CONECT   22    1
CONECT   23    2
CONECT   24    2
CONECT   25    6
CONECT   26    7
CONECT   27    7
CONECT   28    8
CONECT   29    8
CONECT   30    9
CONECT   31    9
CONECT   32    9
CONECT   33   10
CONECT   34   13
CONECT   35   14
CONECT   36   15
CONECT   37   16
CONECT   38   17
CONECT   39   19
CONECT   40   20
END
)";

static molphene::Scene scene;
static GLFWwindow* window;
static bool is_mol_moi = false;
static bool mouse_press = false;
static int mouse_button = -1;
static double delt_x = 0;
static double delt_y = 0;
static double last_x = 0;
static double last_y = 0;

static void
error_callback(int error, const char* description)
{
  fputs(description, stderr);
}

static void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(action == GLFW_PRESS) {
    switch(key) {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(window, GL_TRUE);
      break;
    case GLFW_KEY_P:
      scene.get_camera().projection_mode(true);
      break;
    case GLFW_KEY_O:
      scene.get_camera().projection_mode(false);
      break;
    case GLFW_KEY_E:
      std::stringstream pdbstm;
      if(is_mol_moi) {
        pdbstm.str(pdbhem);
      } else {
        pdbstm.str(pdbmoi);
      }

      is_mol_moi = !is_mol_moi;

      scene.open_stream(pdbstm);
      scene.reset_mesh();
    }
  }
}

static void
window_size_callback(GLFWwindow* window, int w, int h)
{
  scene.change_dimension(w, h);
}

static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  delt_x = 0;
  delt_y = 0;
  glfwGetCursorPos(window, &last_x, &last_y);

  mouse_press = action == GLFW_PRESS;
  mouse_button = button;
}

static void
cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(mouse_press) {
    delt_x = xpos - last_x;
    delt_y = ypos - last_y;

    last_x = xpos;
    last_y = ypos;

    switch(mouse_button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      scene.rotate(delt_y / 80, delt_x / 80, 0);
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:

      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:

      break;
    default:
      break;
    }
  }
}

void
scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  yoffset > 0 ? scene.get_camera().zoom_in() : scene.get_camera().zoom_out();
}

void
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  scene.setup_graphics();
  scene.change_dimension(width, height);
}

bool
init_window(int width, int height)
{
  glfwSetErrorCallback(error_callback);
  if(!glfwInit()) {
    return false;
  }

  window = glfwCreateWindow(width, height, "Simple example", nullptr, nullptr);
  if(!window) {
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetWindowSizeCallback(window, window_size_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  return true;
}

void
render()
{
  scene.render_frame();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void
main_loop()
{
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(render, 0, 1);
#else
  while(!glfwWindowShouldClose(window)) {
    render();
  }
#endif
}

int
main(int argc, char* argv[])
{
  if(!init_window(640, 480)) {
    return EXIT_FAILURE;
  }

  int width = 0, height = 0;

  glfwGetFramebufferSize(window, &width, &height);
  scene.setup_graphics();
  scene.change_dimension(width, height);

  if(argc > 1) {
    std::ifstream pdbfile(argv[1]);
    if(pdbfile.is_open()) {
      std::cout << "openfile success!" << std::endl;

      scene.open_stream(pdbfile);
      scene.reset_mesh();
      main_loop();

      pdbfile.close();
    } else {
      std::cout << "openfile failure!" << std::endl;
    }
  } else {
    std::stringstream pdbstm;
    pdbstm.str(pdbhem);

    scene.open_stream(pdbstm);
    scene.reset_mesh();
    main_loop();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

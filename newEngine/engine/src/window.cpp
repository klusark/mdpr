#include "engineLib.hpp"
#include "window.hpp"

namespace engine{
	namespace window{
		bool isActive = true;
		EngineLib bool createWindow(int screenWidth, int screenHeight, int bitsPerPixel, const char * title, bool fullScreenFlag)
		{
			if (!SDL_WasInit(SDL_INIT_VIDEO)){
				printf("SDL not initializeed\n");
				return false;
			}

		    int videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
			videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
			videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
			videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

			const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo( );
			if (videoInfo->hw_available){
				videoFlags |= SDL_HWSURFACE;
			}else{
				videoFlags |= SDL_SWSURFACE;
			}

			if (videoInfo->blit_hw){
				videoFlags |= SDL_HWACCEL;
			}

			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1 );

			//if (fullScreenFlag)

			SDL_SetVideoMode(screenWidth, screenHeight, bitsPerPixel, videoFlags);


			SDL_WM_SetCaption(title, title);
			

			/* Enable smooth shading */
			glShadeModel( GL_SMOOTH );

			/* Set the background black */
			glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

			/* Depth buffer setup */
			glClearDepth( 1.0f );

			/* Enables Depth Testing */
			glEnable( GL_DEPTH_TEST );

			/* The Type Of Depth Test To Do */
			glDepthFunc( GL_LEQUAL );

			/* Really Nice Perspective Calculations */
			glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

			windowResize(screenWidth, screenHeight);
			return true;
		}

		void windowResize(int width, int height)
		{
			/* Height / width ration */
			GLfloat ratio;

			/* Protect against a divide by zero */
			if ( height == 1 )
				height = 100;

			ratio = ( GLfloat )width / ( GLfloat )height;

			/* Setup our viewport. */
			glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

			/* change to the projection matrix and set our viewing volume. */
			glMatrixMode( GL_PROJECTION );
			glLoadIdentity( );

			/* Set our perspective */
			gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

			/* Make sure we're chaning the model view and not the projection */
			glMatrixMode( GL_MODELVIEW );

			/* Reset The View */
			glLoadIdentity( );
		}

		void draw()
		{
			/* These are to calculate our fps */
			static GLint T0     = 0;
			static GLint Frames = 0;

			/* Clear The Screen And The Depth Buffer */
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			/* Move Left 1.5 Units And Into The Screen 6.0 */
			glLoadIdentity();
			/*glTranslatef( 0.0f, 0.0f, -3.0f );

			glBegin( GL_TRIANGLES );             // Drawing Using Triangles       
			  glVertex3f( -1.1f,  1.0f,  0.0f ); // Top Of Triangle               
			  glVertex3f( -1.0f, -1.0f,  0.0f ); // Left Of Triangle              
			  glVertex3f(  1.0f, -1.0f,  0.0f ); // Right Of Triangle             
			glEnd( );                            // Finished Drawing The Triangle 
			*/
			// Move Right 3 Units 
			glTranslatef( 0.0f, 0.0f, -3.0f );

			// Set The Color To Blue One Time Only 
			glColor3f( 0.5f, 1.0f, 1.0f);
			
			glBegin( GL_QUADS );                 /* Draw A Quad              */
			  glVertex3f(  1.25f,  1.25f,  0.0f ); /* Top Right Of The Quad    */
			  glVertex3f( -1.25f,  1.25f,  0.0f ); /* Top Left Of The Quad     */
			  glVertex3f( -1.25f, -1.25f,  0.0f ); /* Bottom Left Of The Quad  */
			  glVertex3f(  1.25f, -1.25f,  0.0f ); /* Bottom Right Of The Quad */
			glEnd( );                            /* Done Drawing The Quad    */

			/* Draw it to the screen */
			SDL_GL_SwapBuffers( );

			/* Gather our frames per second */
			Frames++;
			
			GLint t = SDL_GetTicks();
			if (t - T0 >= 5000) {
				GLfloat seconds = (t - T0) / 1000.0;
				GLfloat fps = Frames / seconds;
				printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
				T0 = t;
				Frames = 0;
			
			}
		}
	}
}
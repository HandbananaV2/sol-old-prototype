#ifndef UGUISTATICIMAGE_H
#define UGUISTATICIMAGE_H

#include <UGUIComponent.h>
#include <UGUI_Displayable_I.hpp>
#include <UGUI_Positionable.hpp>

class UGUI_StaticImage : public UGUI_Component, public UGUI_Displayable_I, public UGUI_Positionable
{
    public:
        /*
        *
        */
        UGUI_StaticImage(const std::string&);
        /*
        *
        */
        virtual ~UGUI_StaticImage();
		/*
		*
		*/
		virtual void display();
		/*
		*
		*/
		virtual void update(float);
		/*
		*
		*/
		virtual std::string getType() const;
		/*
		*
		*/
		virtual void bindSurface(int, const sf::Texture&) override;
        /*
		*
		*/
		virtual void bindSurface(int, int = 0) override;
        /*
		*
		*/
		virtual const sf::Texture* getTexture(unsigned int index = 0) ;
		/*
		*
		*/
		virtual void setPosition(float, float) ;
		/*
		*
		*/
		virtual sf::Vector2f getPosition() ;
		/*
		*
		*/
		virtual void setSize(float, float, bool logical);
		/*
		*
		*/
		virtual sf::Vector2f getSize(bool) ;

    protected:

    private:
};

#endif // UGUISTATICIMAGE_H

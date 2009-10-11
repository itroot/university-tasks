#ifndef VISUALENTITY_H_
#define VISUALENTITY_H_


#include <vector>

/**
 * Pure virtual class (interface) for object, that can render
 * class Renderer.
 */
 
class VisualEntity {
  public:
  	VisualEntity();
    virtual ~VisualEntity();
    
    virtual void renderMe()=0;
    void renderChildren();
    void render();
    void setThisChildPolicy(bool HowToRender);
    void setTheyChildPolicy(bool HowToRender);
  protected:
    std::vector<VisualEntity*> Children;
  private:
    bool RenderChildren;
};

#endif /*VISUALENTITY_H_*/

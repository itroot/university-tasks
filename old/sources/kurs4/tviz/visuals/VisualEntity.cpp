#include "VisualEntity.h"

VisualEntity::VisualEntity() {
  RenderChildren=true;
}

VisualEntity::~VisualEntity() {

}

void VisualEntity::render() {
  renderMe();
  if (RenderChildren) renderChildren(); 
}

void VisualEntity::setThisChildPolicy(bool HowToRender) {
  RenderChildren=HowToRender; 
}

void VisualEntity::setTheyChildPolicy(bool HowToRender) {
  if (!Children.empty()) {
    std::vector<VisualEntity*>::iterator it;
    for(it=Children.begin();it<Children.end();++it) {
      (*it)->setThisChildPolicy(HowToRender);
      // recursive
      (*it)->setTheyChildPolicy(HowToRender);
    }
  }  
}

void VisualEntity::renderChildren() {
  if (!Children.empty()) {
    std::vector<VisualEntity*>::iterator it;
    for(it=Children.begin();it<Children.end();++it) {
      (*it)->render();
    }
  }  
}

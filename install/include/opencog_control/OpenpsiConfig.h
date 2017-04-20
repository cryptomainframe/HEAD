//#line 2 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
// 
// File autogenerated for the opencog_control package 
// by the dynamic_reconfigure package.
// Please do not edit.
// 
// ********************************************************/

#ifndef __opencog_control__OPENPSICONFIG_H__
#define __opencog_control__OPENPSICONFIG_H__

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace opencog_control
{
  class OpenpsiConfigStatics;
  
  class OpenpsiConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l, 
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      
      virtual void clamp(OpenpsiConfig &config, const OpenpsiConfig &max, const OpenpsiConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const OpenpsiConfig &config1, const OpenpsiConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, OpenpsiConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const OpenpsiConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, OpenpsiConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const OpenpsiConfig &config) const = 0;
      virtual void getValue(const OpenpsiConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;
    
    template <class T>
    class ParamDescription : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string name, std::string type, uint32_t level, 
          std::string description, std::string edit_method, T OpenpsiConfig::* f) :
        AbstractParamDescription(name, type, level, description, edit_method),
        field(f)
      {}

      T (OpenpsiConfig::* field);

      virtual void clamp(OpenpsiConfig &config, const OpenpsiConfig &max, const OpenpsiConfig &min) const
      {
        if (config.*field > max.*field)
          config.*field = max.*field;
        
        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const OpenpsiConfig &config1, const OpenpsiConfig &config2) const
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, OpenpsiConfig &config) const
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const OpenpsiConfig &config) const
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, OpenpsiConfig &config) const
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const OpenpsiConfig &config) const
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const OpenpsiConfig &config, boost::any &val) const
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, OpenpsiConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    template<class T, class PT>
    class GroupDescription : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string name, std::string type, int parent, int id, bool s, T PT::* f) : AbstractGroupDescription(name, type, parent, id, s), field(f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, OpenpsiConfig &top) const
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T (PT::* field);
      std::vector<OpenpsiConfig::AbstractGroupDescriptionConstPtr> groups;
    };
    
class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(OpenpsiConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("max_waiting_time"==(*_i)->name){max_waiting_time = boost::any_cast<double>(val);}
        if("aiml"==(*_i)->name){aiml = boost::any_cast<double>(val);}
        if("chatbot_eva"==(*_i)->name){chatbot_eva = boost::any_cast<double>(val);}
        if("fuzzy_matcher"==(*_i)->name){fuzzy_matcher = boost::any_cast<double>(val);}
        if("duckduckgo"==(*_i)->name){duckduckgo = boost::any_cast<double>(val);}
        if("wolframalpha"==(*_i)->name){wolframalpha = boost::any_cast<double>(val);}
        if("random_sentence_pkd"==(*_i)->name){random_sentence_pkd = boost::any_cast<double>(val);}
        if("random_sentence_blogs"==(*_i)->name){random_sentence_blogs = boost::any_cast<double>(val);}
        if("select_pln_answer"==(*_i)->name){select_pln_answer = boost::any_cast<double>(val);}
        if("pickup"==(*_i)->name){pickup = boost::any_cast<double>(val);}
      }
    }

    double max_waiting_time;
double aiml;
double chatbot_eva;
double fuzzy_matcher;
double duckduckgo;
double wolframalpha;
double random_sentence_pkd;
double random_sentence_blogs;
double select_pln_answer;
double pickup;

    bool state;
    std::string name;

    
}groups;



//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double max_waiting_time;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double aiml;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double chatbot_eva;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double fuzzy_matcher;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double duckduckgo;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double wolframalpha;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double random_sentence_pkd;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double random_sentence_blogs;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double select_pln_answer;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double pickup;
//#line 218 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("OpenpsiConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }
    
    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }
    
    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const OpenpsiConfig &__max__ = __getMax__();
      const OpenpsiConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const OpenpsiConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }
    
    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const OpenpsiConfig &__getDefault__();
    static const OpenpsiConfig &__getMax__();
    static const OpenpsiConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();
    
  private:
    static const OpenpsiConfigStatics *__get_statics__();
  };
  
  template <> // Max and min are ignored for strings.
  inline void OpenpsiConfig::ParamDescription<std::string>::clamp(OpenpsiConfig &config, const OpenpsiConfig &max, const OpenpsiConfig &min) const
  {
    return;
  }

  class OpenpsiConfigStatics
  {
    friend class OpenpsiConfig;
    
    OpenpsiConfigStatics()
    {
OpenpsiConfig::GroupDescription<OpenpsiConfig::DEFAULT, OpenpsiConfig> Default("Default", "", 0, 0, true, &OpenpsiConfig::groups);
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.max_waiting_time = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.max_waiting_time = 10.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.max_waiting_time = 3.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("max_waiting_time", "double", 0, "Max Waiting Time (in seconds)", "", &OpenpsiConfig::max_waiting_time)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("max_waiting_time", "double", 0, "Max Waiting Time (in seconds)", "", &OpenpsiConfig::max_waiting_time)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.aiml = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.aiml = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.aiml = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("aiml", "double", 0, "AIML", "", &OpenpsiConfig::aiml)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("aiml", "double", 0, "AIML", "", &OpenpsiConfig::aiml)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.chatbot_eva = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.chatbot_eva = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.chatbot_eva = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("chatbot_eva", "double", 0, "Chatbot Eva", "", &OpenpsiConfig::chatbot_eva)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("chatbot_eva", "double", 0, "Chatbot Eva", "", &OpenpsiConfig::chatbot_eva)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.fuzzy_matcher = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.fuzzy_matcher = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.fuzzy_matcher = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("fuzzy_matcher", "double", 0, "Fuzzy Matcher", "", &OpenpsiConfig::fuzzy_matcher)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("fuzzy_matcher", "double", 0, "Fuzzy Matcher", "", &OpenpsiConfig::fuzzy_matcher)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.duckduckgo = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.duckduckgo = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.duckduckgo = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("duckduckgo", "double", 0, "DuckDuckGo", "", &OpenpsiConfig::duckduckgo)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("duckduckgo", "double", 0, "DuckDuckGo", "", &OpenpsiConfig::duckduckgo)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.wolframalpha = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.wolframalpha = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.wolframalpha = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("wolframalpha", "double", 0, "WolframAlpha", "", &OpenpsiConfig::wolframalpha)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("wolframalpha", "double", 0, "WolframAlpha", "", &OpenpsiConfig::wolframalpha)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.random_sentence_pkd = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.random_sentence_pkd = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.random_sentence_pkd = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("random_sentence_pkd", "double", 0, "Random Sentence Generator - PKD", "", &OpenpsiConfig::random_sentence_pkd)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("random_sentence_pkd", "double", 0, "Random Sentence Generator - PKD", "", &OpenpsiConfig::random_sentence_pkd)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.random_sentence_blogs = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.random_sentence_blogs = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.random_sentence_blogs = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("random_sentence_blogs", "double", 0, "Random Sentence Generator - blogs", "", &OpenpsiConfig::random_sentence_blogs)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("random_sentence_blogs", "double", 0, "Random Sentence Generator - blogs", "", &OpenpsiConfig::random_sentence_blogs)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.select_pln_answer = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.select_pln_answer = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.select_pln_answer = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("select_pln_answer", "double", 0, "PLN", "", &OpenpsiConfig::select_pln_answer)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("select_pln_answer", "double", 0, "PLN", "", &OpenpsiConfig::select_pln_answer)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.pickup = 0.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.pickup = 1.0;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.pickup = 0.9;
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("pickup", "double", 0, "Pick-up Lines", "", &OpenpsiConfig::pickup)));
//#line 280 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(OpenpsiConfig::AbstractParamDescriptionConstPtr(new OpenpsiConfig::ParamDescription<double>("pickup", "double", 0, "Pick-up Lines", "", &OpenpsiConfig::pickup)));
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 235 "/opt/ros/indigo/lib/python2.7/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(OpenpsiConfig::AbstractGroupDescriptionConstPtr(new OpenpsiConfig::GroupDescription<OpenpsiConfig::DEFAULT, OpenpsiConfig>(Default)));
//#line 353 "/opt/ros/indigo/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<OpenpsiConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__); 
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__); 
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__); 
    }
    std::vector<OpenpsiConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<OpenpsiConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    OpenpsiConfig __max__;
    OpenpsiConfig __min__;
    OpenpsiConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const OpenpsiConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static OpenpsiConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &OpenpsiConfig::__getDescriptionMessage__() 
  {
    return __get_statics__()->__description_message__;
  }

  inline const OpenpsiConfig &OpenpsiConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }
  
  inline const OpenpsiConfig &OpenpsiConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }
  
  inline const OpenpsiConfig &OpenpsiConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }
  
  inline const std::vector<OpenpsiConfig::AbstractParamDescriptionConstPtr> &OpenpsiConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<OpenpsiConfig::AbstractGroupDescriptionConstPtr> &OpenpsiConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const OpenpsiConfigStatics *OpenpsiConfig::__get_statics__()
  {
    const static OpenpsiConfigStatics *statics;
  
    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = OpenpsiConfigStatics::get_instance();
    
    return statics;
  }


}

#endif // __OPENPSIRECONFIGURATOR_H__
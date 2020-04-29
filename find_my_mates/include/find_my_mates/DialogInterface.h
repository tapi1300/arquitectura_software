#ifndef DIALOGINTERFACE__H
#define DIALOGINTERFACE__H

#include <ros/ros.h>
#include <string>
#include <dialogflow_ros_msgs/DialogflowResult.h>
#include <boost/algorithm/string/replace.hpp>
#include <std_srvs/Empty.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <sound_play/Talk.h>
#include <regex>
#include <map>

namespace gb_dialog
{
class DialogInterface
{
public:
  using DialogflowResult = dialogflow_ros_msgs::DialogflowResult;

  DialogInterface();

  bool speak(std::string str);
  bool listen();
  virtual void listenCallback(DialogflowResult result){}
  void registerCallback(
    std::function<void(const DialogflowResult & result)> cb,
    std::string intent = "(.*)");

private:
  bool idle_;
  ros::NodeHandle nh_;
  std::string results_topic_, start_srv_;
  ros::ServiceClient talk_client_, sound_client_;
  ros::Subscriber df_result_sub_;
  ros::Publisher listening_gui_, speak_gui_;
  std::regex intent_re_;

  std::map<std::string, std::function<void(const DialogflowResult & result)>> registered_cbs_;


  void init();
  void dfCallback(const DialogflowResult::ConstPtr& result);
};
};  // namespace gb_dialog

#endif

#include <find_my_mates/DialogInterface.h>

#include <string>
#include <utility>

namespace find_my_mates
{

DialogInterface::DialogInterface() : nh_()
{
  init();
}

void DialogInterface::init()
{
  if (!nh_.getParam("/dialogflow_client/results_topic", results_topic_))
    results_topic_ = "/dialogflow_client/results";
  if (!nh_.getParam("/dialogflow_client/start_srv", start_srv_))
    start_srv_ = "/dialogflow_client/start";

  df_result_sub_ = nh_.subscribe(results_topic_, 1, &DialogInterface::dfCallback, this);
  talk_client_ = nh_.serviceClient<sound_play::Talk>("/dialog/talk");
  listening_gui_ = nh_.advertise<std_msgs::Bool>("/dialog_gui/is_listening", 1, true);
  speak_gui_ = nh_.advertise<std_msgs::String>("/dialog_gui/talk", 1, true);

  std_msgs::String str_msg;
  std_msgs::Bool bool_msg;
  str_msg.data = "";
  speak_gui_.publish(str_msg);
  bool_msg.data = false;
  listening_gui_.publish(bool_msg);
}

void DialogInterface::registerCallback(
  std::function<void(const DialogflowResult & result)> cb,
  std::string intent)
{
  registered_cbs_.insert(
    std::pair<std::string, std::function<void(const DialogflowResult & result)>>
    (intent, cb));
}

void DialogInterface::dfCallback(const DialogflowResult::ConstPtr& result)
{ 
  auto bool_msg = std_msgs::Bool();
  bool_msg.data = false;
  listening_gui_.publish(bool_msg);

  if (result->intent.size() > 0)
  {
    for (auto item : registered_cbs_)
    {
      std::regex intent_re = std::regex(item.first);
      if (std::regex_match(result->intent, intent_re))
      {
        
        item.second(*result);
      }
    }
  }
}

bool DialogInterface::speak(std::string str)
{
  boost::replace_all(str, "_", " ");
  std_msgs::String msg;
  msg.data = str;
  speak_gui_.publish(msg);
  sound_play::Talk srv;
  srv.request.str = str;
  talk_client_.call(srv);
}

bool DialogInterface::listen()
{
  std_srvs::Empty srv;
  std_msgs::Bool msg;
  msg.data = true;
  listening_gui_.publish(msg);
  ROS_INFO("[DialogInterface] listening...");
  ros::ServiceClient df_srv = nh_.serviceClient<std_srvs::Empty>(start_srv_, 1);
  df_srv.call(srv);
  return true;
}

};  // namespace gb_dialog

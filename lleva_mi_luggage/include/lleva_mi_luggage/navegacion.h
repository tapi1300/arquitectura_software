
namespace navigation
{
	class Navigator
	{
  	public:
    	Navigator(ros::NodeHandle& nh);
    	void ir_a_pos();
    	void step();

  	private:
    	int posicion = 0;
    	int num_posiciones = 3;
    	bool goal_sended_;
    	ros::NodeHandle nh_;
    	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;
	};
}

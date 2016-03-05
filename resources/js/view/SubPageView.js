var SubPageView = Backbone.View.extend({
	
	initialize:function(){
		_(this).bindAll("render","off","activate");
	},

  show:function(args){
    this.$el.removeClass("off");
	setTimeout(this.activate, 10);
	setTimeout(this.render, 100, args);
  },
  hide:function(){
	this.$el.removeClass("active");
	setTimeout(this.off, 100);
  },
  off:function(){
    this.$el.addClass("off")
  },
  activate:function(){
	  this.$el.addClass("active");
  }

});

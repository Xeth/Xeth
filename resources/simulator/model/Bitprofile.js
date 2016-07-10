var ProfileSimulator = Backbone.Model.extend({

    idAttribute: "uri",

    initialize:function(data, options){
        _(this).bindAll("updateURI");
        this.updateURI();
    },
    
    exportKey:function(){
        return true;
    },
    
    updateURI:function(){
        this.set("uri",this.get("id")+"@"+this.get("context"));
    },

    get:function(key){
        if(key=="uri"||key=="id"||key=="context"||key=="account"||key=="details"||key=="loaded")
        {
            return Backbone.Model.prototype.get.call(this, key);
        }
    },
    
    linkStealthAddress:function(data){
        console.log(data);
        setTimeout(function(model){
            model.set("payments", data.stealth);
        }, 6000, this);
        return true;
    },
    changeURI:function(data){
        console.log(data);
        //return false;
        setTimeout(function(model){
            model.set("context", data.context);
            model.set("id", data.id);
            model.updateURI();
        }, 6000, this);
        return true;
    },
    changePayments:function(data){
        console.log(data);
        //return false;
        setTimeout(function(model){
            model.set("payments", data.stealth);
        }, 6000, this);
        return true;
    },
    changeDetails:function(data){
        console.log(data);
        //return false;
        setTimeout(function(model){
            model.set("name", data.name);
            model.set("avatar", data.avatar);
            model.trigger("change:details", model);
        }, 6000, this);
        return true;
    }

});

var ProfileCollectionSimulator = ProfileCollection.extend({

    initialize:function(){
        _(this).bindAll("add","generate");
    },
    
    model: ProfileSimulator,

    observe: function(){},
    fetch:function(){},

    generate:function(request){
        var profile = request;//{context:request.context, id:request.id, stealth:request.stealth, name:request.name, avatar:request.avatar};
		profile.uri = profile.id+"@"+profile.context;
        this.add(profile);
		return profile;
    },

    create:function(request){
        console.log(request);
        this.trigger("create", request);
        setTimeout(this.generate, 3000, request);
        return true;
    },

    edit:function(request){
        var uri = request.profile.id+"@"+request.profile.context;
        var profile = this.get(uri);
        
        if(!profile.edit(request)) return false;
        this.trigger("edit", request);
        //setTimeout(this.generate, 3000, request);
        return true;
    },

    importKey:function(file, password){
        this.generate({context:"d000", id:"profile_"+Math.random()}); //, stealth:Math.random()
        return true;
    },

    sync:function(){},

    add:function(data){
        data.uri = data.id+"@"+data.context;
        var profile = this.get(data.uri);
        if(!profile)
        {
            Backbone.Collection.prototype.add.call(this, data);
        }
    },
    
    feeDestination:function(){
        return "0x000000";
    },
    
    feeAmount:function(){
        return 1.5;
    }

});

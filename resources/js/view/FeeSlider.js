var FeeSlider = Backbone.View.extend({

    initialize:function(){
        _(this).bindAll("change", "renderFee", "disable");
        
        this.lastFeeFactor = 100;
        this.feeHolder = this.$el.find(".fee .eth");
        this.gasHolder = this.$el.find(".fee .gas");
        this.feeFactor = this.$el.find('.slider');
        this.feeFactor.slider({min:0, max:200, value:this.lastFeeFactor, start:this.change, change:this.change, slide:this.renderFee});
        this.update({gas:0,price:0,fee:"0.0000000000000"});
        
        this.$el.tooltip({
            position: { my: "center top", at: "center bottom" },
            show: { duration: 200 },
            hide: { duration: 200 }
        });
    },
    
    disable:function(result){
        this.update({gas:0,price:0,fee:"0.0000000000000"});
        this.$el.addClass("readonly");
    },
    
    update:function(result){
        this.$el.removeClass("readonly");
        this.gasAmount = result["gas"];
        this.gasPrice = result["price"];
        this.fee = result["fee"];
        this.renderFee(false);
    },
    
    change:function(event,ui){
        this.trigger("change", ui.value);
    },

    renderFee: function(event,ui){
        var fee;
        var factor = ((ui)?ui.value:this.getFeeFactor());
        
        if(event!=false){
            var factorMovement = factor/this.lastFeeFactor;
            fee = this.lastFee*factorMovement;
            fee = ((isNaN(fee))?0:fee).toFixed(13);
            this.trigger("autoupdate", fee);
        }else{
            if(factor==0){
                this.fee="0.0000000000000";
            }else{
                this.lastFeeFactor = this.getFeeFactor();
                this.lastFee = this.fee;
            }
            fee = this.fee;
        }
        if(factor<90){
            this.feeFactor.addClass("warning");
        }else{
            this.feeFactor.removeClass("warning");
        }
        
        this.feeHolder.html(fee?fee.substr(0, 15):0);
        this.gasHolder.html(((this.gasAmount)?this.gasAmount:0));
    },
    
    getFeeFactor: function(){
        var gas = this.feeFactor.slider("value");
        return parseInt(gas); //in percents
    },
    
    hasWarning:function(){
        return this.feeFactor.hasClass("warning");
    }
});

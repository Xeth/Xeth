
var TransactionView = Backbone.View.extend({
    initialize:function(options){
        var data = this.model.toJSON();
        data.amount = splitAmount(data.amount);
        this.$el = $(options.template({transaction:data}));
    }
});


function TransactionViewFactory(template){

    this.create = function(model){
        return new TransactionView({model:model, template:template});
    }
    return this;
}


var TransactionsPageView = SubPageView.extend({

    initialize:function(options){
        _(this).bindAll("setTimeFilter", "setAddressFilter", "setTypeFilter");
		SubPageView.prototype.initialize.call(this,options);
        this.totalSent = 0;
        this.totalReceived = 0;
        this.template = options.templates.get("transactions");
        this.$el.html(this.template());
        this.accounts = options.accounts;
        this.filters = {timeStart:null, timeEnd:null, address:null, type:null};
        this.factory = new TransactionViewFactory(options.templates.get("transaction_item"));
        this.collection = new CollectionView({
            collection:options.transactions,
            factory:this.factory,
            scroll:true,
            reversed:false,
            ordered:true,
            el:this.$el.find(".transactionList"),
            empty:this.$el.find(".empty")
        });

        this.$sent = this.$el.find(".transactions_total .sent .txtBalance");
        this.$received = this.$el.find(".transactions_total .received .txtBalance");

        var dateInput = this.$el.find('.daterange');
        dateInput.daterangepicker({
            "showDropdowns": true, 
            "autoApply": true, 
            "startDate": "2015-11-01", 
            "endDate": moment(), 
            "opens": "left",
            locale: {format: 'YYYY-MM-DD'},
            ranges: {
               'All Time': ["2015-11-01", moment()],
               'Today': [moment(), moment()],
               'Yesterday': [moment().subtract(1, 'days'), moment().subtract(1, 'days')],
               'Last 7 Days': [moment().subtract(6, 'days'), moment()],
               'Last 30 Days': [moment().subtract(29, 'days'), moment()],
               'This Month': [moment().startOf('month'), moment().endOf('month')],
               'Last Month': [moment().subtract(1, 'month').startOf('month'), moment().subtract(1, 'month').endOf('month')]
            }
        }, this.setTimeFilter);
        dateInput.on('change.daterangepicker', function(ev, picker) {
            if(picker)
                $(this).val(picker.chosenLabel);
            else
                $(this).val("All Time");
        }).trigger('change.daterangepicker');

        this.typeFilter = this.$el.find("#filterTransactionType");
		this.typeFilter.selectmenu();
		this.typeFilter.on("selectmenuchange",this.setTypeFilter);
		
        this.listenTo(this.accounts, "change", this.setAddressFilter);
        this.listenTo(options.transactions, "add", this.updateTotal);
        this.listenTo(options.transactions, "reset", this.computeTotals);
        this.computeTotals();
    },

    render:function(options){
        this.accounts.resize(21);
        this.accounts.compact(true);
        this.accounts.attach(this.$el.find("#filterTransactionAddress"));
        this.accounts.filter(function(){return true;}); //show all rows
        this.accounts.style("mini");
        if(options && options.focusFirst) this.collection.focusFirst();
    },

    setTimeFilter:function(start, end, label){
        if(label=='All Time'){
            this.filters.timeStart = this.filters.timeEnd = null
        }else{
            this.filters.timeStart = start;
            this.filters.timeEnd = end;
        }
        console.log('New date range selected: ' + start + ' to ' + end );
        this.applyFilters();
    },

    setTypeFilter:function(ev){
        var type = (!ev.target)? ev : $(ev.target).val();
        this.filters.type = type=="All"?null:type;
        this.applyFilters();
    },

    setAddressFilter:function(model){
        var address = !model ? null : model.get("address")||model.get("stealth");
        this.filters.address = address;
        this.applyFilters();
    },

    applyFilters:function(){
        var filters = this.filters;
        this.collection.filter(function(model){

            if(filters.timeStart&&filters.timeEnd){
                var time = model.get("timestamp");
                if(time<filters.timeStart||time>filters.timeEnd) return false;
            }

            if(filters.address && filters.address != model.get("from") && filters.address != model.get("to")) return false;
            if(filters.type && filters.type!=model.get("category")) return false;

            return true;
        });
        this.computeTotals();
    },

    computeTotals: function(){
        var sent = 0;
        var received = 0;
        this.collection.each(function(view){
            if(view.$el.is(":hidden")) return;
            var model = view.model;
            if(model.get("category")=="Sent")
                sent += model.get("amount");
            else
                received += model.get("amount"); //including mined
        });
        this.totalSent = sent;
        this.totalReceived = received;
        this.renderTotals();
    },

    updateTotal: function(model){
        if(model.get("type")=="Sent")
            this.totalSent += model.get("amount");
        else
            this.totalReceived += model.get("amount"); //including mined
        this.renderTotals();
    },

    renderTotals:function(){
        var sent = splitAmount(this.totalSent);
        var received = splitAmount(this.totalReceived);
        this.$sent.find(".int").html(sent.int);
        this.$sent.find(".dec").html(sent.dec);
        this.$received.find(".int").html(received.int);
        this.$received.find(".dec").html(received.dec);
    }
});
